#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "sha256.h"
	#include <sys/socket.h> 
	#include <netinet/in.h> 
	#include <arpa/inet.h> 
    
    #define BUFFER_SIZE 1024
	#define MAX_USERNAME 50
	#define MAX_PASSWORD 50
    
	struct User {
	   char username[MAX_USERNAME + 1];
	   char hashed_password[BUFFER_SIZE + 1];
	};
    
    void register(int sockfd, struct User *user) {
       char buffer[BUFFER_SIZE];
       send(sockfd, "Username: ", 9, 0);
       recv(sockfd, buffer, BUFFER_SIZE, 0);
       strncpy(user->username, buffer, MAX_USERNAME + 1);
       user->username[MAX_USERNAME] = '\0';
       
       send(sockfd, "Password: ", 9, 0);
       recv(sockfd, buffer, BUFFER_SIZE, 0);
       strncpy(user->hashed_password, sha256(buffer), BUFFER_SIZE + 1);
       user->hashed_password[BUFFER_SIZE] = '\0';
    }
    
    int main() {
        int sockfd; 
	    struct sockaddr_in servaddr, cli; 
	    
	    // Create a socket
	    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
	        perror("socket creation failed"); 
	        exit(EXIT_FAILURE); 
	    } 
	    
	    memset(&servaddr, 0, sizeof(servaddr)); 
	    memset(&cli, 0, sizeof(cli)); 
        
        servaddr.sin_family = AF_INET; // IPv4 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        servaddr.sin_port = htons(8080); 
	    
	    // Bind the socket to a address and port
	    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
	        perror("socket bind failed"); 
	        exit(EXIT_FAILURE); 
	    } 
        
        struct User user;
        register(sockfd, &user);
        
	    // Listen to the socket for incoming connections
	    listen(sockfd, 3); 
	    
	    int clilen = sizeof(cli); 
	    int newsockfd = accept(sockfd, (struct sockaddr *)&cli, &clilen); 
	    if (newsockfd < 0) { 
	        perror("accept failed"); 
	        exit(EXIT_FAILURE); 
	    } 
        
        send(newsockfd, user.hashed_password, BUFFER_SIZE, 0);
	    
	    return 0; 
	}