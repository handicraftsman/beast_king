#include "simple_router.hpp"
#include "app.hpp"
#include "version.hpp"

namespace http = boost::beast::http;
using     tcp  = boost::asio::ip::tcp;

using req_t = boost::beast::http::request<boost::beast::http::string_body>;
using res_t = boost::beast::http::response<boost::beast::http::string_body>;

BeastKing::SimpleRouter::SimpleRouter() {}
BeastKing::SimpleRouter::~SimpleRouter() {}

void BeastKing::SimpleRouter::route(boost::beast::http::verb verb, const std::string& rgx, BeastKing::SimpleRouterHandler handler, bool premake) {
  std::tuple<std::regex, bool, BeastKing::SimpleRouterHandler> tpl { std::regex(rgx), premake, handler };
  route_map[verb].push_back(tpl);
}

void BeastKing::SimpleRouter::handle(BeastKing::ContextPtr ctx) {
  const std::string sname = BOOST_BEAST_VERSION_STRING + std::string(" - BeastKing " BEAST_KING_VERSION);

  for (const std::tuple<std::regex, bool, BeastKing::SimpleRouterHandler>& tpl : route_map[ctx->req->method()]) {
    std::regex rgx;
    bool premake;
    BeastKing::SimpleRouterHandler handler;
    std::tie(rgx, premake, handler) = tpl;

    std::string pathname(ctx->url->pathname());

    std::smatch m {};

    if ((m = std::smatch {}, std::regex_match(pathname, m, rgx))) {
      if (premake) {
        ctx->res = std::shared_ptr<res_t>(new res_t(http::status::bad_request, ctx->req->version()));
        ctx->res->set(http::field::server, sname);
        ctx->res->set(http::field::content_type, "text/plain");
        ctx->res->keep_alive(ctx->req->keep_alive());
        ctx->res->prepare_payload();
      }

      handler(ctx, m);

      if (premake) {
        boost::system::error_code ec;
        http::response_serializer<http::string_body, http::fields> sr(*(ctx->res.get()));
        http::write(*(ctx->sock.get()), sr, ec);
        if (ec)
          BeastKing::fail(ec, "http::write");
      }
    }
  }
}