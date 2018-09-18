#include "server_threaded.hpp"
#include "log.hpp"

#include <chrono>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <thread>

using tcp = boost::asio::ip::tcp;

BeastKing::ServerThreaded::ServerThreaded(AppPtr app, const std::string& addr)
: BeastKing::Server(app, addr)
{}

BeastKing::ServerThreaded::~ServerThreaded() {}

void BeastKing::ServerThreaded::runner() {
  std::regex rgx("(.+):(\\d{1,5})");
  
  std::smatch m;
  
  if (!std::regex_match(addr, m, rgx)) {
    throw std::runtime_error("Unable to parse address");
  }

  std::string host = m[1];
  int port = std::stoi(m[2]);

  std::shared_ptr<boost::asio::io_context> ioc(new boost::asio::io_context { 1 });

  tcp::acceptor acceptor(
    *ioc.get(),
    tcp::acceptor::endpoint_type(
      boost::asio::ip::make_address(host),
      static_cast<unsigned short>(port)
    )
  );

  BOOST_LOG(app->logger) << "Serving on " << host << ":" << port;

  for (;;) {
    std::shared_ptr<tcp::socket> sock(new tcp::socket(*ioc.get()));
    acceptor.accept(*sock);
    std::thread thr([this, ioc, sock] () {
      try {
        BeastKing::ContextPtr ctx(new BeastKing::Context(ioc, sock));

        using tp_t = std::chrono::time_point<std::chrono::system_clock>;
        using dr_t = std::chrono::duration<std::chrono::system_clock>;

        tp_t t1 = std::chrono::system_clock::now();

        app->handle(ctx);

        tp_t t2 = std::chrono::system_clock::now();

        auto d = t2 - t1;

        auto dv = std::chrono::duration_cast<std::chrono::milliseconds>(d);

        BOOST_LOG(app->logger)
          << "> "
          << ctx->req->method()
          << " "
          << ctx->url->pathname()
          << " "
          << ctx->res->result_int()
          << " "
          << dv.count()
          << "ms";
      } catch (const std::exception& exc) {
        char* exc_name = abi::__cxa_demangle(typeid(exc).name(), nullptr, nullptr, nullptr);
        std::cout << exc_name << " - " << exc.what() << std::endl;
      }
    });
    thr.detach();
  }

}