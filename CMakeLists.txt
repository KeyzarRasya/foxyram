cmake_minimum_required(VERSION 3.28)
project(foxyram)

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

file(WRITE ${CMAKE_BINARY_DIR}/foxyram.service
"
[Unit]
Description=Foxyram Server
After=network.target

[Service]
ExecStart=/usr/local/bin/foxyram

[Install]
WantedBy=default.target
"
)

add_executable(foxyram ${SERVER_SOURCES})
add_executable(foxyram-cli ${CLI_SOURCES})

install(TARGETS foxyram DESTINATION /usr/local/bin)
install(FILES ${CMAKE_BINARY_DIR}/foxyram.service DESTINATION /etc/systemd/system)

install(TARGETS foxyram-cli DESTINATION /usr/local/bin)

add_custom_target(enable_service
	COMMAND systemctl daemon-reload
	COMMAND systemctl enable foxyram.service
	COMMAND systemctl start foxyram.service
)
