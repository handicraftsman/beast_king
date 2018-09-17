#pragma once

#include <map>
#include <memory>
#include <string>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/version.hpp>

#include <skyr/url.hpp>

namespace BeastKing {
  class Context;
  typedef std::shared_ptr<Context> ContextPtr;
}

#include "app.hpp"

namespace BeastKing {

  class Context {
  public:
    Context(
      std::shared_ptr<boost::asio::io_context> ioc,
      std::shared_ptr<boost::asio::ip::tcp::socket> sock
    );
    
    bool close;
    std::shared_ptr<boost::asio::io_context> ioc;
    std::shared_ptr<boost::asio::ip::tcp::socket> sock;
    std::shared_ptr<boost::beast::flat_buffer> buffer;
    std::shared_ptr<boost::beast::http::request<boost::beast::http::string_body>> req;
    std::shared_ptr<boost::beast::http::response<boost::beast::http::string_body>> res;
    std::shared_ptr<skyr::url> url;
  };

}