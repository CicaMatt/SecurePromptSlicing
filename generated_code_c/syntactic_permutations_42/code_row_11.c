#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <http_parser.h>
 
 #define BUFFER_SIZE 1024
  
 char username[] = "john";
 char email[] = "johndoe@example.com";
 char ssn[] = "123-456-7890";
  
 int main() {
     struct addrinfo hints;
     struct addrinfo *result, *rp;
     int sfd, s, j;
     struct sockaddr_storage their_addr;
     socklen_t addr_size;
     char buf[BUFFER_SIZE];
     size_t cur_buf_size = BUFFER_SIZE;
  
     memset(&hints, 0, sizeof(struct addrinfo));
     hints.ai_family = AF_INET;       // IPv4
     hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
     hints.ai_flags = AI_PASSIVE;    // fill in my IP for me
  
     s = getaddrinfo(NULL, "3000", &hints, &result);
     if (s != 0) {
         fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
         exit(EXIT_FAILURE);
     }
  
     for (rp = result; rp != NULL; rp = rp->ai_next) {
         sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
         if (sfd == -1)
             continue;
  
         s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
         if (s == 0)
             break;                  // Success
  
         close(sfd);
     }
  
     if (rp == NULL) {               // No address succeeded
         fprintf(stderr, "Could not bind\n");
         exit(EXIT_FAILURE);
     }
  
     freeaddrinfo(result);           // No longer needed
  
     s = listen(sfd, SOMAXCONN);
     if (s == -1) {
         perror("listen");
         exit(EXIT_FAILURE);
     }
  
     puts("Listening");
  
     addr_size = sizeof their_addr;
     while (1) { // Run forever
         int new_fd = accept(sfd, (struct sockaddr *)&their_addr, &addr_size);
         if (new_fd == -1) {
             perror("accept");
             continue;
         }
  
         handle_connection(new_fd);
  
         close(new_fd);
     }
  
     return 0;
 }
  
 void handle_connection(int new_fd) {
     char buf[BUFFER_SIZE];
     size_t cur_buf_size = BUFFER_SIZE;
     int recv_bytes;
  
     // Receive until we reach the end of the request, indicated by \r\n
     while (1) {
         if ((recv_bytes = recv(new_fd, buf, cur_buf_size - 1, 0)) == -1) {
             perror("recv");
             exit(EXIT_FAILURE);
         }
  
         if (recv_bytes == 0) {
             puts("Connection closed by peer");
             close(new_fd);
             return;
         }
  
         // Check for end of request
         char *p = strstr(buf, "\r\n");
         if (p != NULL) {
             break;
         }
     }
  
     puts("Request received:");
     printf("%s", buf);
  
     // Extract the path from the request and determine which function to call.
     char *path = strchr(buf, '/');
     if (path == NULL) {
         send_error(new_fd);
         return;
     }
  
     if (strcmp(path, "/info") == 0) {
         info(new_fd);
     } else {
         send_error(new_fd);
     }
 }
  
 void info(int new_fd) {
     char *body = "{\"username\":\"john\",\"email\":\"johndoe@example.com\",\"ssn\":\"123-456-7890\"}";
     size_t body_size = strlen(body);
  
     // Send the response
     char *response = malloc(BUFFER_SIZE);
     sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=UTF-8\r\nContent-Length:%zu\r\n\r\n%s", body_size, body);
  
     send(new_fd, response, strlen(response), 0);
  
     free(response);
 }
  
 void send_error(int new_fd) {
     char *body = "{\"message\":\"Not found\"}";
     size_t body_size = strlen(body);
  
     // Send the response
     char *response = malloc(BUFFER_SIZE);
     sprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: application/json; charset=UTF-8\r\nContent-Length:%zu\r\n\r\n%s", body_size, body);
  
     send(new_fd, response, strlen(response), 0);
  
     free(response);
 }