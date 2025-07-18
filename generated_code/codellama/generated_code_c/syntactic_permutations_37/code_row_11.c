#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0); //Create a new socket
    struct hostent *host;
    host = gethostbyname("127.0.0.1"); //Get the IP address of the server we want to connect to.
    
    if(host == NULL) {
        printf("Could not find host\n");
        exit(1);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET; //Create a new socket address for the server we want to connect to.
    memcpy((char *)&server.sin_addr.s_addr, host->h_addr, host->h_length); 
    server.sin_port = htons(3001);
    
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) { //Connect to the server.
        perror("Connect failed.");
        exit(1);
    }
    
    printf("Connected.\n");
    char send_buffer[256];
    recv(sock, send_buffer, sizeof(send_buffer), 0); //Receive data from the server.
    if(strcmp(send_buffer, "Username:") == 0){
        printf("Sending username...\n");
        char name[32];
        fgets(name, 32, stdin);
        send(sock, name, strlen(name), 0); //Send the username to the server.
    } else if (strcmp(send_buffer, "Password:") == 0){
        printf("Sending password...\n");
        char pass[32];
        fgets(pass, 32, stdin);
        send(sock, pass, strlen(pass), 0); //Send the password to the server.
    } else {
        printf("%s", send_buffer);
    }
    
    close(sock);
}