# Usage:
# FIND_PACKAGE(boost REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name boost)
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

if(NOT boost_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(boost URL https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz)
    FetchContent_GetProperties(boost)

    if(NOT boost_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(boost)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

        # ADD_SUBDIRECTORY(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
        # message(${boost_SOURCE_DIR})
        include_directories(${boost_SOURCE_DIR})
        SET(boost_FOUND TRUE)
    endif()
endif()