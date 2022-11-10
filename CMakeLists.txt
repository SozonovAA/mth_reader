cmake_minimum_required(VERSION 3.14)

project(myprg
    VERSION 1.0.0
    DESCRIPTION "Template for C++ project with CMake"
    LANGUAGES CXX)



#--------------------------------------------------------------
# submodule section
# here we use the following code to support
# old versions of git(that don't download submodule
# contents automatically).
#--------------------------------------------------------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update
      --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT
    )
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "Git submodule update --init failed with ${GIT_SUBMODULE_RESULT}, Please checkout submodules")
    endif()
  endif()
endif()
#
#----------------------------------------------------
#use some lib


option(MYPRG_BUILD_TESTS "Build mylib tests" ON)
option(MYPRG_BUILD_EXAMPLES "Build mylib examples" ON)
option(USE_SOME_LIB "A simple lib for smth" OFF)

if(USE_SOME_LIB)
    message("USE_SOME_LIB")

    list(APPEND EXTRA_INCLUDE_DIRS "some_lib")
    list(APPEND EXTRA_LIB_DIRS "some_lib")
    list(APPEND EXTRA_LINKS pqxx)
endif()
configure_file(src/config/MyPrgConfig.h.in src/config/MyPrgConfig.h @ONLY)

include(GNUInstallDirs)

list(APPEND     main_source
                src/main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${main_source})

list(APPEND     src_sources
                src/include/inc.h
                src/sources/inc.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${src_sources})

add_executable(${PROJECT_NAME}
               ${main_source}
               ${src_sources}
               )


target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}
           ${EXTRA_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC
    ${EXTRA_LIB_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${EXTRA_LINKS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE )
set(CPACK_PACKAGING_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGING_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
include(CPack)

if(MYPRG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MYPRG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
