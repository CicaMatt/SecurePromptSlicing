#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* hash a password */
char* hash_password(const char* password){
    /* hash the password using SHA-256 or any other method you prefer */
    return "hashed_password";
}

int main(){
    int client_socket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /* create a socket for the client */
    if((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("client: can't open stream socket");
        exit(1);
    }

    /* set up the server address */
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891); 
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    /* connect to the server */
    if(connect(client_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
        perror("client: can't connect to server");
        exit(1);
    }

    /* username and password variables */
    char* username = "user";
    const char* password = "password";

    /* hash the password */
    char* hashed_password = hash_password(password);

    printf("Sending username and password to server...\n");

    /* send the username and hashed password to the server */
    write(client_socket, &username, strlen(username));
    write(client_socket, &hashed_password, strlen(hashed_password));

    printf("Username and password sent!\n");
}