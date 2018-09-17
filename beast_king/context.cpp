#include "context.hpp"

BeastKing::Context::Context(
  std::shared_ptr<boost::asio::io_context> ioc,
  std::shared_ptr<boost::asio::ip::tcp::socket> sock
)
: close(false)
, ioc(ioc)
, sock(sock)
{}