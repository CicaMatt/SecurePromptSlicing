#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <netdb.h>
    
    typedef struct session {
      char *username;
      char *email;
      int ssn;
    } Session;
    
    void info(int socket) {
      printf("HTTP/1.0 200 OK\r\n");
      printf("<html><body>");
      printf("Username: %s<br>", ((Session *)get_session())->username);
      printf("Email: %s<br>", ((Session *)get_session())->email);
      printf("SSN: %d<br>", ((Session *)get_session())->ssn);
      printf("</body></html>");
    }
    
    int main(int argc, char const *argv[]) {
      struct sockaddr_in server;
      int socket_desc, client_sock, c, read_size;
      struct sockaddr_in client;
      socklen_t client_len = sizeof(struct sockaddr_in);
    
      // Create socket
      socket_desc = socket(AF_INET, SOCK_STREAM, 0);
      if (socket_desc == -1) {
        printf("Could not create socket\n");
        return -1;
      }
      puts("Socket created");
    
      // Prepare the sockaddr_in structure
      server.sin_family = AF_INET;
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_port = htons(8080);
    
      // Bind
      if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        return -1;
      }
      puts("Bind done");
    
      // Listen
      listen(socket_desc, 3);
    
      // Accept and incoming connection
      puts("Waiting for incoming connections...");
      c = sizeof(struct sockaddr_in);
    
      // Handle requests
      while (1) {
        client_sock = accept(socket_desc, (struct sockaddr *)&client, &client_len);
        if (client_sock < 0) {
          perror("accept failed");
          return -1;
        }
    
        puts("Connection accepted");
    
        char buffer[256];
        read(client_sock, buffer, 255);
    
        if (strstr(buffer, "GET /info") != NULL) {
          info(client_sock);
        } else {
          printf("HTTP/1.0 404 NOT FOUND\r\n");
          printf("<html><body>Not found</body></html>\r\n");
        }
    
        close(client_sock);
      }
    
      return 0;
    }