#pragma once

#include "server.hpp"

namespace BeastKing {

  class ServerThreaded : public Server {
  public:
    ServerThreaded(AppPtr app, const std::string& addr);
    virtual ~ServerThreaded();

  protected:
    void runner() override;
  };

}