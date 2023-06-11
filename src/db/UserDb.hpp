#ifndef CRUD_USERDB_HPP
#define CRUD_USERDB_HPP

#include "../dto/UserDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class UserDb : public oatpp::orm::DbClient
{
public:
  UserDb(const std::shared_ptr<oatpp::orm::Executor> &executor) : oatpp::orm::DbClient(executor)
  {
    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");

    migration.migrate();

    v_int64 version = executor->getSchemaVersion();
    OATPP_LOGD("userDb", "Migration - OK. version=%lld", version);
  }

  QUERY(createUser,
        "INSERT INTO AppUser"
        "(username, email, password, role) VALUES "
        "(:user.username, :user.email, :user.password, :user.role);",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(updateUser,
        "UPDATE AppUser "
        "SET "
        " username=:user.username, "
        " email=:user.email, "
        " password=:user.password, "
        " role=:user.role "
        "WHERE "
        " id=:user.id;",
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(getUserById,
        "SELECT * FROM AppUser WHERE id=:id;",
        PARAM(oatpp::Int32, id))

  QUERY(getAllUsers,
        "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteUserById,
        "DELETE FROM AppUser WHERE id=:id;",
        PARAM(oatpp::Int32, id))
};

#include OATPP_CODEGEN_END(DbClient)

#endif