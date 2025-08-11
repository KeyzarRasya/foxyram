cmake_minimum_required(VERSION 3.28)
project(ridaore)

include_directories(include)

set(
	SERVER_SOURCES 
	main.c 
	src/server.c
	ds/linkedlist.c
	ds/set.c
)

set(
	CLI_SOURCES
	client.c
	src/client.c 
	src/shell.c
)

file(WRITE ${CMAKE_BINARY_DIR}/ridaore.service
"
[Unit]
Description=Ridaore Server
After=network.target

[Service]
ExecStart=/usr/local/bin/ridaore

[Install]
WantedBy=default.target
"
)

add_executable(ridaore ${SERVER_SOURCES})
add_executable(ridaore-cli ${CLI_SOURCES})

install(TARGETS ridaore DESTINATION /usr/local/bin)
install(FILES ${CMAKE_BINARY_DIR}/ridaore.service DESTINATION /etc/systemd/system)

install(TARGETS ridaore-cli DESTINATION /usr/local/bin)

add_custom_target(enable_service
	COMMAND systemctl daemon-reload
	COMMAND systemctl enable ridaore.service
	COMMAND systemctl start ridaore.service
)
