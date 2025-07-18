#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 5000

struct product{
    int code;
    int price;
};

int get_code(int x){
    struct product p;
    p.code = x;
    return p.code;
}

void calculate(int y, int z){
    int total = y*z;
    printf("Total: %d\n",total);
}

void *process_request(void *arg){
    
    struct sockaddr_in client_address;
    char buffer[1024] = {0};
    char *message;
    int client_socket, addrlen = sizeof(client_address);
    getsockname(client_socket, (struct sockaddr *)&client_address, &addrlen);
    read(client_socket, buffer, 1024);
    char *code = strtok(buffer, " ");
    int c_code = atoi(code);
    get_code(c_code);
    char *quantity = strtok(NULL, " ");
    int qty = atoi(quantity);
    calculate(p.price, qty);
}
int main(){
    
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    pthread_t thread_id;
    char buffer[1024] = {0};
    char *message;
    int addrlen = sizeof(client_address);
    
    // create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Listening...\n");
    
    while(1){
        
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen);
        message = "Hello! This is the web server";
        send(client_socket, message, strlen(message), 0);
        getsockname(client_socket, (struct sockaddr *)&client_address, &addrlen);
        
        pthread_create(&thread_id, NULL, process_request, (void*) client_socket);
    }
    return 0;
}