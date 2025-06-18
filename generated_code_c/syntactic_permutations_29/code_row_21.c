#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <string.h>
    #include <regex.h>
    
    void send_message(int socket, const char* message) {
      int n = strlen(message);
      if (send(socket, message, n, 0) < n) {
        perror("Send failed");
      }
    }
    
    int redirect_to_example(const char* target) {
      regex_t re;
      int match = regcomp(&re, ".*example.com", REG_EXTENDED);
      if (match != 0) {
        char buffer[256];
        regerror(match, &re, buffer, sizeof(buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", buffer);
        return -1;
      }
    
      int status = regexec(&re, target, 0, NULL, 0);
      if (status != REG_NOMATCH) {
        char redirect[256];
        sprintf(redirect, "Location: %s\r\n", target);
        send_message(socket, redirect);
      } else {
        send_message(socket, "Location: /\r\n");
      }
    
      regfree(&re);
    
      return 0;
    }
    
    int main() {
      struct addrinfo hints;
      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;
    
      struct addrinfo* bind_address;
      getaddrinfo(NULL, "80", &hints, &bind_address);
    
      int socket_fd = socket(bind_address->ai_family,
                             bind_address->ai_socktype,
                             bind_address->ai_protocol);
      if (socket_fd == -1) {
        perror("Socket creation failed");
        return 0;
      }
    
      int enable = 1;
      if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
        perror("Set socket option failed");
        return 0;
      }
    
      if (bind(socket_fd, bind_address->ai_addr, bind_address->ai_addrlen) == -1) {
        perror("Bind failed");
        return 0;
      }
    
      freeaddrinfo(bind_address);
    
      if (listen(socket_fd, 3) == -1) {
        perror("Listen failed");
        return 0;
      }
    
      char target[256];
      ssize_t received = recv(socket_fd, target, 256, 0);
      if (received == -1) {
        perror("Receive failed");
        return 0;
      }
    
      const char* http_request = "GET /?target=https://www.example.com HTTP/1.1\r\n";
      target[received] = '\0';
      if (strncmp(http_request, target, strlen(http_request)) == 0) {
        const char* location = "Location: https://www.example.com\r\n";
        send_message(socket_fd, location);
      } else {
        const char* not_found = "HTTP/1.1 404 Not Found\r\n\r\n";
        send_message(socket_fd, not_found);
      }
    
      close(socket_fd);
    
      return 0;
    }