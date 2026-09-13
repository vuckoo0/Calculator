cmake_minimum_required(VERSION 3.16)

project(Calculator LANGUAGES C)

add_executable(calculator
	source/calculator.c
)

target_compile_features(calculator PRIVATE c_std_11)

target_include_directories(calculator PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(UNIX AND NOT APPLE)
	target_link_libraries(calculator PRIVATE m)
endif()
