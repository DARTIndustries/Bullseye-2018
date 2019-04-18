//Networking Driver
//3/2/2019
//DART
//author: Adam (everyone)
#pragma once
#include <stdlib.h>
#include <commands/CommandUnion.h>

#define PORT 8000 

class NetworkingDriver {
private:
	int _socket = -1;
public:
	void open_connection();
	void close_connection();
	CommandUnion* read_command();
	int read_packet(void* buf, size_t buf_size);
	int send_packet(void* buf, size_t buf_size);
};

