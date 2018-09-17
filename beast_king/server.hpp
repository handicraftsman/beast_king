#pragma once

#include <memory>
#include <string>

namespace BeastKing {
  class Server;
  typedef std::shared_ptr<Server> ServerPtr;
}

#include "app.hpp"
#include "context.hpp"

namespace BeastKing {

  class Server {
  public:
    Server(AppPtr app, const std::string& addr);
    virtual ~Server();

    void run();

  protected:
    virtual void runner();

    AppPtr app;
    std::string addr;
  };

}