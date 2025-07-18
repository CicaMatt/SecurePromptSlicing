#include <stdio.h>
#include <stdlib.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080

void ping(char *url) {
    char command[50] = "ping ";
    strcat(command, url);

    system(command);
}