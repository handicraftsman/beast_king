#include "app.hpp"
#include "version.hpp"

#include <iostream>
#include <string>

#include <skyr/url.hpp>

namespace http = boost::beast::http;
using     tcp  = boost::asio::ip::tcp;

using req_t = boost::beast::http::request<boost::beast::http::string_body>;
using res_t = boost::beast::http::response<boost::beast::http::string_body>;

BeastKing::App::App() {}

void BeastKing::fail(boost::system::error_code ec, char const* what) {
  throw std::runtime_error(std::string(what) + ": " + ec.message());
}

void BeastKing::App::handle(BeastKing::ContextPtr ctx) {
  const std::string sname = BOOST_BEAST_VERSION_STRING + std::string(" - BeastKing " BEAST_KING_VERSION);

  boost::system::error_code ec;

  ctx->buffer = std::shared_ptr<boost::beast::flat_buffer>(new boost::beast::flat_buffer());
  ctx->req    = std::shared_ptr<req_t>(new req_t());
  ctx->close  = true;

  http::read(*(ctx->sock.get()), *(ctx->buffer.get()), *(ctx->req.get()), ec);

  std::string target = ctx->req->target().to_string();
  std::string host = ctx->req->base().at("Host").to_string();

  auto base_url = skyr::make_url("http://" + host);
  ctx->url = std::shared_ptr<skyr::url>(new skyr::url(target, base_url.value()));

  if (router) {
    router->handle(ctx);
  } else {
    ctx->res = std::shared_ptr<res_t>(new res_t(http::status::bad_request, ctx->req->version()));
    ctx->res->set(http::field::server, sname);
    ctx->res->set(http::field::content_type, "text/plain");
    ctx->res->keep_alive(ctx->req->keep_alive());
    ctx->res->body() = "No router specified!";
    ctx->res->prepare_payload();
    http::response_serializer<http::string_body, http::fields> sr(*(ctx->res.get()));
    http::write(*(ctx->sock.get()), sr, ec);
  }

  if (ec == http::error::end_of_stream)
    return;
  if (ec)
    fail(ec, "boost::beast::http::read");

  ctx->sock->shutdown(tcp::socket::shutdown_send, ec);
}