cmake_minimum_required(VERSION 3.14)
project(mth_rd-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------


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
# external sources
#----------------------------------------------------------------------------------------------------------------------
list(APPEND ext_sources
    ../../prog/src/sources/mthreader.cpp
    )

#----------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------
# tests sources
#----------------------------------------------------------------------------------------------------------------------

list(APPEND test_sources
    searchTest.cpp
    fileReadTest.cpp
    mthReaderTest.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${test_sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(mth_rd-tests)
target_sources(mth_rd-tests PRIVATE ${test_sources} ${ext_sources})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
