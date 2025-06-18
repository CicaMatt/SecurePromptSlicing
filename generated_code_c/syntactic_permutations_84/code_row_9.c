#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

//Defining the port number for our socket to listen on
#define PORT 8080

int main() {
    //Declare variables that will be used later
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    
    //Create a socket using the socket() function
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Socket failed\n");
        exit(EXIT_FAILURE);
    }
    
    //Setting all values in address to zero
    memset(&address, 0, sizeof(address));
    
    //Set IPv4 address family
    address.sin_family = AF_INET;
    
    //Set port number using htons() function
    address.sin_port = htons(PORT);
    
    //Set the listening IP address to any
    address.sin_addr.s_addr = INADDR_ANY;
    
    //Forcefully attaching socket to a particular port 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        printf("Bind failed\n");
        exit(EXIT_FAILURE);
    }
    
    //Listening to incoming connections using listen() function
    if (listen(server_fd, 3) < 0){
        printf("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
            printf("Accept failed\n");
            exit(EXIT_FAILURE);
        }
        
        //Receive data from client using recv() function
        valread = read(new_socket, buffer, 1024);
        
        //Send some data to the client using send() function
        if (send(new_socket, hello, strlen(hello), 0) < 0){
            printf("Send failed\n");
            exit(EXIT_FAILURE);
        }
    }
}