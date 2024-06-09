cmake_minimum_required(VERSION 3.5)

project(befcompiler)

set(SOURCES
	src/lexer.cpp
	src/parser_td.cpp
	src/parser_bd.cpp
	src/main.cpp
)

add_executable(befcompiler ${SOURCES})

target_include_directories(befcompiler
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)