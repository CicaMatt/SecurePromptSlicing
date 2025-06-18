#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void check_mod(int socket, char* username, char* password)
{
  if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
    send(socket, "true", strlen("true"), 0);
  }
  else
  {
    send(socket, "false", strlen("false"), 0);
  }
}