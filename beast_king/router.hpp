#pragma once

#include <memory>
#include <string>

namespace BeastKing {
  class Router;
  typedef std::shared_ptr<Router> RouterPtr;
}

#include "context.hpp"

namespace BeastKing {

  class Router {
  public:
    virtual ~Router();

    virtual void handle(ContextPtr ctx) = 0;
  };

}