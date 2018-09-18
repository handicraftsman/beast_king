#pragma once

#include <memory>
#include "log.hpp"

namespace BeastKing {
  class App;
  typedef std::shared_ptr<App> AppPtr;
}

#include "context.hpp"
#include "router.hpp"

namespace BeastKing {
  namespace src = boost::log::sources;

  void fail(boost::system::error_code ec, char const* what);

  class App {
  public:
    App();

    void handle(ContextPtr ctx);

    boost::log::sources::logger logger;
    RouterPtr router;
  };

}