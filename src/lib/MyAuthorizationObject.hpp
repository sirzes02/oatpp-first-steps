#ifndef AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_
#define AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_

#include <oatpp/web/server/handler/AuthorizationHandler.hpp>

class MyAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject
{
public:
  MyAuthorizationObject(const oatpp::String &pUserId)
      : userId(pUserId)
  {
  }

  oatpp::String userId;
};

/**
 * Implementation of a custom BasicAuthorizationHandler to streamline the authorization process
 * using basic authorization
 */
class MyBearerAuthorizationHandler : public oatpp::web::server::handler::BearerAuthorizationHandler
{
public:
  MyBearerAuthorizationHandler()
      : BearerAuthorizationHandler("my-realm")
  {
  }

  std::shared_ptr<AuthorizationObject> authorize(const oatpp::String &token) override
  {
    if (token == "4e99e8c12de7e01535248d2bac85e732")
    {
      return std::make_shared<MyAuthorizationObject>("uid-admin");
    }

    return nullptr;
  }
};

#endif // AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_