#include <beast_king.hpp>
#include <beast_king/server_threaded.hpp>
#include <beast_king/simple_router.hpp>
#include <boost/beast/http/verb.hpp>

#include <functional>

namespace http = boost::beast::http;

class MyApp : public BeastKing::App {
public:
  MyApp() {
    using namespace std::placeholders;

    auto r = new BeastKing::SimpleRouter();

    r->get("^.*$", [&] (BeastKing::ContextPtr ctx, std::smatch m) {
      std::string res = "Hello, World!";
      ctx->res->body() = res;
      ctx->res->content_length(res.size());
    });

    BeastKing::App::router = BeastKing::RouterPtr(r);
  }
};

int main(int argc, char** argv) {
  BeastKing::AppPtr app(new MyApp());
  BeastKing::ServerPtr server(new BeastKing::ServerThreaded(app, "0.0.0.0:8080"));
  server->run();
  return 0;
}