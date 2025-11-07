cmake_minimum_required(VERSION 3.10)

project(decodificador VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE _ALL_CPP RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")
set(PROJECT_SOURCES "")
foreach(_f IN LISTS _ALL_CPP)
  # Skip files generated under the binary dir (default: build/)
  if(_f MATCHES "^build/")
    # skip files that are inside the build directory
  else()
    list(APPEND PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/${_f}")
  endif()
endforeach()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

find_package(Doxygen)
option(BUILD_DOCS "Build Doxygen documentation (requires Doxygen)" ON)
if(BUILD_DOCS AND DOXYGEN_FOUND)
  set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/Doxyfile)
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
else()
  if(BUILD_DOCS)
    message(STATUS "Doxygen not found: documentation target 'doc' will not be available. Install doxygen or set BUILD_DOCS=OFF.")
  endif()
endif()

message(STATUS "Project '${PROJECT_NAME}' configured. Sources: ${PROJECT_SOURCES}")
