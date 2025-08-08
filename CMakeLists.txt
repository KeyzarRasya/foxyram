cmake_minimum_required(VERSION 3.28)
project(foxyram)

include_directories(include)

set(
	SOURCES 
	main.c 
	src/server.c
	ds/linkedlist.c
	ds/set.c
)

add_executable(foxyram ${SOURCES})
