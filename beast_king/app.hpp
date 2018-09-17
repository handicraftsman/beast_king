#pragma once

#include <memory>

namespace BeastKing {
  class App;
  typedef std::shared_ptr<App> AppPtr;
}

#include "context.hpp"
#include "router.hpp"

namespace BeastKing {

  void fail(boost::system::error_code ec, char const* what);

  class App {
  public:
    App();

    void handle(ContextPtr ctx);

    RouterPtr router;
  };

}