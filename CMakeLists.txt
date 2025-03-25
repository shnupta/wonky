cmake_minimum_required(VERSION 3.12)

project(wonky
    VERSION 0.0.1
		DESCRIPTION "A tui library"
    HOMEPAGE_URL "https://github.com/shnupta/wonky")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
	hulaloop
	GIT_REPOSITORY https://github.com/shnupta/hulaloop.git
	GIT_TAG main
)
FetchContent_MakeAvailable(hulaloop)

set(WONKY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${WONKY_INCLUDE_DIR})

add_library(wonky INTERFACE)
add_library(wonky::wonky ALIAS wonky)
target_link_libraries(wonky INTERFACE hulaloop::hulaloop)

set(_wonky_is_toplevel_project FALSE)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(_wonky_is_toplevel_project TRUE)
endif()

target_include_directories(
    wonky
    INTERFACE
		$<BUILD_INTERFACE:${WONKY_INCLUDE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_definitions(wonky INTERFACE "")

if (_wonky_is_toplevel_project)
	# message("wonky => building tests")
	# add_subdirectory(tests)
	message("wonky => building demos")
	add_subdirectory(demos)
endif()
