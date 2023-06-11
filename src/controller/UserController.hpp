
#ifndef UserController_hpp
#define UserController_hpp

#include "service/UserService.hpp"
#include "lib/MyAuthorizationObject.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

using namespace oatpp::web::server::handler;

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController
{
public:
  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {
    setDefaultAuthorizationHandler(std::make_shared<MyBearerAuthorizationHandler>());
  }

private:
  UserService m_userService; // Create user service.
public:
  static std::shared_ptr<UserController> createShared(
      OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  )
  {
    return std::make_shared<UserController>(objectMapper);
  }

  ENDPOINT_INFO(createUser)
  {
    info->summary = "Create new User";

    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "users", createUser,
           BODY_DTO(Object<UserDto>, userDto))
  {
    return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
  }

  ENDPOINT_INFO(putUser)
  {
    info->summary = "Update User by userId";

    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("PUT", "users/{userId}", putUser,
           PATH(Int32, userId),
           BODY_DTO(Object<UserDto>, userDto))
  {
    userDto->id = userId;
    return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
  }

  ENDPOINT_INFO(getUserById)
  {
    info->summary = "Get one User by userId";

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("GET", "users/{userId}", getUserById,
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
  }

  ENDPOINT_INFO(getUsersPagination)
  {
    info->summary = "get all stored users in pagination";

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsersPagination,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getAllUsersPagination(offset, limit));
  }

  ENDPOINT_INFO(getAllUsers)
  {
    info->summary = "get all stored users";

    info->addResponse<oatpp::Vector<UserDto::Wrapper>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_401, "application/json");

    std::list<oatpp::String> listaDeStrings = {"read"};
    std::shared_ptr<std::__cxx11::list<oatpp::String>> sharedPtrLista = std::make_shared<std::__cxx11::list<oatpp::String>>(listaDeStrings);

    info->addSecurityRequirement("bearerAuth", sharedPtrLista);
  }
  ENDPOINT("GET", "users", getAllUsers, AUTHORIZATION(std::shared_ptr<MyAuthorizationObject>, authObject))
  {
    OATPP_ASSERT_HTTP(authObject->userId == "uid-admin", Status::CODE_401, "Unauthorized");

    return createDtoResponse(Status::CODE_200, m_userService.getAllUsers());
  }

  ENDPOINT_INFO(deleteUser)
  {
    info->summary = "Delete User by userId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "users/{userId}", deleteUser,
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
  }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* UserController_hpp */