#include "server.hpp"

#include <stdexcept>

BeastKing::Server::Server(BeastKing::AppPtr app, const std::string& addr)
: app(app)
, addr(addr)
{}

BeastKing::Server::~Server() {}

void BeastKing::Server::run() {
  runner();
}

void BeastKing::Server::runner() {
  throw std::runtime_error("Do not use BeastKing::Server directly!");
}