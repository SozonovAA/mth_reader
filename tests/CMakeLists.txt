cmake_minimum_required(VERSION 3.14)
project(mth_rd-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------
set(Boost_USE_STATIC_LIBS ON)
add_definitions(-DBOOST_PYTHON_STATIC_LIB)
set(Boost_USE_MULTITHREADED ON)

find_package( Boost 1.74 COMPONENTS program_options thread timer chrono REQUIRED )
message(STATUS "Boost version: ${Boost_VERSION}")
if(Boost_FOUND)
    list(APPEND EXTRA_INCLUDE_DIRS
        ${Boost_INCLUDE_DIR} )

    list(APPEND EXTRA_LINKS
        ${Boost_LIBRARIES} )
else()
    message(BOOST NOT FOUND)
endif()

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
    ../../prog/src/sources/search.cpp
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

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}
           ${EXTRA_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC
    ${EXTRA_LIB_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest_main
    ${EXTRA_LINKS})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
