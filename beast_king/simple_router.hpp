#pragma once

#include <functional>
#include <map>
#include <regex>
#include <tuple>
#include <vector>

#include <boost/beast/http/verb.hpp>

namespace BeastKing {
  class SimpleRouter;
}

#include "router.hpp"

namespace BeastKing {

  typedef std::function<void(ContextPtr, std::smatch)> SimpleRouterHandler;

  class SimpleRouter : public Router {
  public:

    typedef std::map<boost::beast::http::verb, std::vector<std::tuple<std::regex, bool, SimpleRouterHandler>>> RouteMap;

    SimpleRouter();
    virtual ~SimpleRouter();

    void route(boost::beast::http::verb verb, const std::string& rgx, SimpleRouterHandler handler, bool premake = true);

    inline void get(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::get, rgx, handler, premake);
    }
    
    inline void head(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::head, rgx, handler, premake);
    }
    
    inline void post(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::post, rgx, handler, premake);
    }
    
    inline void put(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::put, rgx, handler, premake);
    }
    
    inline void connect(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::connect, rgx, handler, premake);
    }
    
    inline void options(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::options, rgx, handler, premake);
    }
    
    inline void trace(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::trace, rgx, handler, premake);
    }
    
    inline void delete_(const std::string& rgx, SimpleRouterHandler handler, bool premake = true) {
      route(boost::beast::http::verb::delete_, rgx, handler, premake);
    }

    void handle(ContextPtr ctx) override;

  private:
    RouteMap route_map;
  };

}