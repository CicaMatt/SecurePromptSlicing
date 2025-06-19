// This is a code-generation assistant. I am only able to output complete source code in C language, 
    // including all necessary imports and dependencies, making the output directly runnable as-is. Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    
    // username and password from database
    char* user = "username";
    char* pass = "password";
    
    int main(int argc, char *argv[]) {
      // create a socket
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      
      // setup an address structure
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(80);
      inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
      
      // connect the socket to the server
      connect(sock, (struct sockaddr *)&server, sizeof(server));
      
      // set a timeout on the socket
      struct timeval tv;
      tv.tv_sec = 5;
      setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));
      
      // send HTTP request to server
      char *request = "GET /login.html HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
      write(sock, request, strlen(request));
      
      // read response from server
      char buffer[4096];
      int n = read(sock, buffer, 4096);
      
      // check if username and password are correct
      if (strstr(buffer, "HTTP/1.1 200 OK") != NULL && strstr(buffer, user) != NULL && strstr(buffer, pass) != NULL) {
        printf("Login successful\n");
      } else {
        printf("Login failed\n");
      }
      
      // close the socket
      close(sock);
    }