cmake_minimum_required(VERSION 3.17)

project(R-type)

set(CMAKE_CXX_STANDARD 17)

set(SERVER_BINARY_NAME r-type_server)
set(CLIENT_BINARY_NAME r-type_client)

if(UNIX)
    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
endif(UNIX)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g3")

# Paths
set(SRC_SERVER src/server)
set(SRC_CLIENT src/client)
set(SRC_GAME src/game)

# Include directories
include_directories(include/)
include_directories(include/server)
include_directories(include/client)
include_directories(include/game)

# Compilation
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)

find_package(raylib REQUIRED)
find_package(boost COMPONENTS system REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)

IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(${SERVER_BINARY_NAME} ${SRC_SERVER}/main.cpp ${SRC_SERVER}/Server.cpp ${SRC_SERVER}/Room.cpp ${SRC_SERVER}/ServerInternalLogic.cpp ${SRC_SERVER}/System.cpp ${SRC_CLIENT}/ClientInternalLogic.cpp ${SRC_GAME}/Entity.cpp ${SRC_GAME}/Menu.cpp ${SRC_GAME}/Lobby.cpp ${SRC_SERVER}/serialize.cpp)

add_executable(${CLIENT_BINARY_NAME} ${SRC_CLIENT}/main.cpp ${SRC_CLIENT}/ClientInternalLogic.cpp ${SRC_SERVER}/Room.cpp ${SRC_GAME}/Entity.cpp ${SRC_SERVER}/ServerInternalLogic.cpp ${SRC_SERVER}/System.cpp ${SRC_GAME}/Menu.cpp ${SRC_GAME}/Lobby.cpp ${SRC_SERVER}/serialize.cpp ${SRC_GAME}/fire.hpp)

# target_link_libraries(${CLIENT_BINARY_NAME} ${USED_LIBS})
# target_link_libraries(${SERVER_BINARY_NAME} ${USED_LIBS})
target_link_libraries(r-type_client raylib)
target_link_libraries(r-type_server raylib)
#target_link_libraries(r-type_client -lboost_system)
#target_link_libraries(r-type_server -lboost_system)


set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Wintrack")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

install(TARGETS r-type_client RUNTIME DESTINATION bin)
install(TARGETS r-type_server RUNTIME DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets" DESTINATION "bin")

# set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_SOURCE_DIR}/build/;${CMAKE_SOURCE_DIR}/.git/")
set(CPACK_GENERATOR "ZIP")

include(CPack)