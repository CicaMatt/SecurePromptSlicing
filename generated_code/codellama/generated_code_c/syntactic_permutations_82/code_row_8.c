#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Request {
    char *method;
    char *url;
};

void parse_request(char *request, struct Request *req) {
    // split request into method and url parts
    char *token = strtok(request, " \n");
    req->method = token;
    
    token = strtok(NULL, " \n");
    req->url = token;
}

void handle_connection(int sock) {
    // read the request from the socket
    char request[1024] = {0};
    int n = recv(sock, request, sizeof(request), 0);
    
    // parse the request
    struct Request req = {0};
    parse_request(request, &req);
    
    printf("Method: %s\n", req.method);
    printf("URL: %s\n", req.url);
    
    // create a dictionary to store the payload
    struct Payload {
        char *name;
    };
    
    struct Payload payload = {0};
    
    // load the payload into the dictionary
    char *token = strtok(req.url, "&");
    while (token != NULL) {
        if (strncmp("name=", token, 5) == 0) {
            payload.name = token + 5;
        }
        
        token = strtok(NULL, "&");
    }
    
    // return the name value from the dictionary
    char response[1024] = {0};
    sprintf(response, "Name: %s\n", payload.name);
    send(sock, response, strlen(response), 0);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // creating a socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(4000);
    
    // binding the socket to localhost and port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        printf("\n\tListening for incoming connections...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_connection(new_socket);
    }
}