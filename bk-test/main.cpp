#include <cstdlib>

#include <functional>

#include <beast_king/server_threaded.hpp>

#ifndef BOOST_LOG_DYN_LINK
#define BOOST_LOG_DYN_LINK 1
#endif

#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/support/date_time.hpp>

#include "app.hpp"

int main(int argc, char** argv) {

  char* h_ = getenv("HOST");
  std::string h = h_ == NULL ? "0.0.0.0" : std::string(h_);

  char* p_ = getenv("PORT");
  std::string p = p_ == NULL ? "8080" : std::string(p_);

  std::string addr = h + ":" + p;

  boost::log::add_console_log(std::clog, boost::log::keywords::format = "%TimeStamp%: %Message%");
  boost::log::add_common_attributes();

  BeastKing::AppPtr app(new MyApp());
  BeastKing::ServerPtr server(new BeastKing::ServerThreaded(app, addr));
  server->run();
  return 0;
}