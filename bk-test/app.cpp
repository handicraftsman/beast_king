#include "app.hpp"

#include <beast_king/context.hpp>
#include <beast_king/router.hpp>
#include <beast_king/simple_router.hpp>
#include <boost/beast/http/verb.hpp>

namespace http = boost::beast::http;
using namespace std::placeholders;

MyApp::MyApp() {
  auto r = new BeastKing::SimpleRouter();

  r->get("^.*$", [&] (BeastKing::ContextPtr ctx, std::smatch m) {
    ctx->res->result(http::status::ok);
    std::string res = "Hello, World!";
    ctx->res->body() = res;
    ctx->res->content_length(res.size());
  });

  BeastKing::App::router = BeastKing::RouterPtr(r);
}