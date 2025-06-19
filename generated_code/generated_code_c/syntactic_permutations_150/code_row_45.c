#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <arpa/inet.h>

void post(){
    char name[256];
    char message[1024];
    char sql[2048];

    strcpy(name, request.getParameter("name"));
    strcpy(message, request.getParameter("message"));

    sprintf(sql, "INSERT INTO messages (name, message) VALUES ('%s', '%s')", name, message);

    insert_user_message_in_db(sql);

    redirect("/");
}

void main(){
    int sockfd; 
    char buffer[2048]; 
    struct sockaddr_in serverAddress; 
    struct hostent *serverHostInfo;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (sockfd < 0){
        printf("Error creating socket!\n");
        exit(1);
    }
    
    serverHostInfo = gethostbyname("localhost"); 

    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(3000); 
    serverAddress.sin_addr = *((struct in_addr *)serverHostInfo->h_addr); 
    memset(&(serverAddress.sin_zero), '\0', 8); 
    
    connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)); 

    while (1){
        printf("> ");
        fgets(buffer, 2048, stdin);

        send(sockfd, buffer, strlen(buffer), 0); 

        memset(buffer, 0, 2048); 
        recv(sockfd, buffer, 2048, 0); 

        printf("%s", buffer); 
    }
    
    close(sockfd);
}