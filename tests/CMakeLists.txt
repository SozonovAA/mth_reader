cmake_minimum_required(VERSION 3.14)
project(myprg-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

#string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

#if(is_top_level)
#    enable_testing()
#endif()

#----------------------------------------------------------------------------------------------------------------------
# testing framework
#----------------------------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # do not override parent project's runtime settings on Windows
set(INSTALL_GTEST OFF)

# For simplicity, always build googletest as static library. This prevents mylib-tests executable from
# complaining about missing googletest DLLs on Windows.
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)

#----------------------------------------------------------------------------------------------------------------------
# tests dependencies
#----------------------------------------------------------------------------------------------------------------------

#if(is_top_level)
#    find_package(mylib REQUIRED)
#endif()

#----------------------------------------------------------------------------------------------------------------------
# tests sources
#----------------------------------------------------------------------------------------------------------------------

set(sources
    test.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(myprg-tests)
target_sources(myprg-tests PRIVATE ${sources})

target_link_libraries(myprg-tests
        PRIVATE
        gtest_main)

#add_test(
#      NAME myprg-tests
#      COMMAND $<TARGET_FILE:myprg-tests>
#      )

include(GoogleTest)
gtest_discover_tests(myprg-tests)
