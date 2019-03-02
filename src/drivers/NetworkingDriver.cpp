#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <drivers/NetworkingDriver.h>


/**
 * Reads on the opened socket into buf up to buf_size bytes. Throws an exception if socket is not opened
 */
int NetworkingDriver::read_packet(void* buf, size_t buf_size) {
    if (_socket == -1) {
        //TODO: Throw exception
    }
    return read(_socket, buf, buf_size); 
}


void NetworkingDriver::send_packet(void* buf, size_t buf_size) {
    if (_socket == -1) {
        //TODO: Throw exception
    }
    send(_socket, buf, buf_size, 0);
}

//TODO: Replace exits with throws to an exception
//TODO: Close server fd?
/** Opens a socket and calls accept on port
 * Once a connection is made it returns a socket
 * Blocking call
 */
void NetworkingDriver::open_connection() {
    int server_fd; 
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    int opt = 1; 

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0)  { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
}
