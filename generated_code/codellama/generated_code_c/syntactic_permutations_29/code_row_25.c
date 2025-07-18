#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "http_parser.h"
#define BUFFERSIZE 1024
#define MAXLINE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char request[BUFFERSIZE];
    char response[MAXLINE];
    regex_t target_regex;
    regcomp(&target_regex,"http://example.com",REG_EXTENDED);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(80);
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while(1){
      socklen_t client_size = sizeof(client);
      if ((client_fd = accept(server_fd, (struct sockaddr *)&client, &client_size)) > 0) {
        read(client_fd, request, BUFFERSIZE);
        sscanf(request,"GET /?target=%s",response);
        regex_t target_regex;
        regcomp(&target_regex,"http://example.com",REG_EXTENDED);
        if (regexec(&target_regex,response,0,NULL,0)==0){
          sprintf(response,"HTTP/1.1 302 Found\r\nLocation: %s\r\nConnection: close\r\n",response);
        } else {
          sprintf(response,"HTTP/1.1 302 Found\r\nLocation: /\r\nConnection: close\r\n");
        }
        write(client_fd, response, MAXLINE);
      }
    }
    return 0;
}