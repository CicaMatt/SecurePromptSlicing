#include <stdint.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    
    int do_login(int port, char *ip) {
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      server.sin_addr.s_addr = inet_addr(ip);
    
      int client_socket = socket(AF_INET, SOCK_STREAM, 0);
      connect(client_socket, (struct sockaddr *)&server, sizeof(server));
    
      char *request;
      asprintf(&request, "GET /login HTTP/1.1\r\nHost: %s:%d\r\nConnection: close\r\n\r\n", ip, port);
    
      send(client_socket, request, strlen(request), 0);
      free(request);
    
      char response[4096];
      recv(client_socket, &response, sizeof(response), 0);
    
      // Parse the response.
      char *token = strtok(response, "\r\n");
      while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "\r\n");
      }
    
      close(client_socket);
      return 0;
    }
    
    int index(int port, char *ip) {
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      server.sin_addr.s_addr = inet_addr(ip);
    
      int client_socket = socket(AF_INET, SOCK_STREAM, 0);
      connect(client_socket, (struct sockaddr *)&server, sizeof(server));
    
      char *request;
      asprintf(&request, "GET /index HTTP/1.1\r\nHost: %s:%d\r\nConnection: close\r\n\r\n", ip, port);
    
      send(client_socket, request, strlen(request), 0);
      free(request);
    
      char response[4096];
      recv(client_socket, &response, sizeof(response), 0);
    
      // Parse the response.
      char *token = strtok(response, "\r\n");
      while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "\r\n");
      }
    
      close(client_socket);
      return 0;
    }
    
    int user_page(int port, char *ip, char *username) {
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      server.sin_addr.s_addr = inet_addr(ip);
    
      int client_socket = socket(AF_INET, SOCK_STREAM, 0);
      connect(client_socket, (struct sockaddr *)&server, sizeof(server));
    
      char *request;
      asprintf(&request, "GET /user/%s HTTP/1.1\r\nHost: %s:%d\r\nConnection: close\r\n\r\n", username, ip, port);
    
      send(client_socket, request, strlen(request), 0);
      free(request);
    
      char response[4096];
      recv(client_socket, &response, sizeof(response), 0);
    
      // Parse the response.
      char *token = strtok(response, "\r\n");
      while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "\r\n");
      }
    
      close(client_socket);
      return 0;
    }
    
    int admin_page(int port, char *ip) {
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      server.sin_addr.s_addr = inet_addr(ip);
    
      int client_socket = socket(AF_INET, SOCK_STREAM, 0);
      connect(client_socket, (struct sockaddr *)&server, sizeof(server));
    
      char *request;
      asprintf(&request, "GET /admin HTTP/1.1\r\nHost: %s:%d\r\nConnection: close\r\n\r\n", ip, port);
    
      send(client_socket, request, strlen(request), 0);
      free(request);
    
      char response[4096];
      recv(client_socket, &response, sizeof(response), 0);
    
      // Parse the response.
      char *token = strtok(response, "\r\n");
      while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "\r\n");
      }
    
      close(client_socket);
      return 0;
    }