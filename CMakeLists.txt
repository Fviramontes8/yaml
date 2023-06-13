cmake_minimum_required(VERSION 3.8...3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION.${CMAKE_MINOR_VERSION})
endif()

project(YAML
	VERSION 1.0 
	DESCRIPTION "Yet Another Matrix Library"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yaml_bench main.cpp matrix.hpp)
