cmake_minimum_required(VERSION 3.1)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/lib/MyAuthorizationObject.hpp 
        src/controller/StaticController.hpp
        src/controller/UserController.hpp
        src/db/UserDb.hpp
        src/dto/UserDto.hpp
        src/dto/StatusDto.hpp
        src/dto/PageDto.hpp
        src/service/UserService.hpp
        src/service/UserService.cpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/ErrorHandler.hpp
        src/ErrorHandler.cpp
        src/SwaggerComponent.hpp
)

## link libs

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestClient.hpp
        test/app/TestDatabaseComponent.hpp
        test/app/TestComponent.hpp
        test/UserControllerTest.hpp
        test/UserControllerTest.cpp
)

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
