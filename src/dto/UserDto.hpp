#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
     VALUE(GUEST, 0, "ROLE_GUEST"),
     VALUE(ADMIN, 1, "ROLE_ADMIN"))

ENUM(Status, v_int32,
     VALUE(INACTIVE, 0, "STATUS_INACTIVE"),
     VALUE(ACTIVE, 1, "STATUS_ACTIVE"))

class UserDto : public oatpp::DTO
{
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");
  DTO_FIELD(Enum<Role>::AsString, role, "role");

  DTO_FIELD(Enum<Status>::AsString, status, "status") = Status::ACTIVE;

  DTO_FIELD_INFO(creation_date)
  {
    info->description = "creation date, by default";
  }
  DTO_FIELD(Int64, creation_date, "creation_date") = static_cast<Int64>(time(nullptr));
};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */