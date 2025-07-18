#include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <string.h>
  #include <ctype.h>
  #include "http_parser.h"
  #define PORT 8080

  struct request {
    const char *name;
    int fd;
  };

  void img(int fd, char* name) {
      printf("opening %s\n", name);
      int file_fd = open(name, O_RDONLY);
      if (file_fd == -1) {
          perror("Could not open");
      } else {
          struct request req = { .name = "img", .fd = fd };
          send_response(req, file_fd);
      }
  }

  int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char *message = "Hello, client!";

    // Create the socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Assign a socket to the port
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accepting client connections
    while (1) {
      socklen_t client_size = sizeof(client);
      if ((client_fd = accept(server_fd, (struct sockaddr *)&client, &client_size)) < 0) {
          perror("accept");
          continue;
      }

      char buffer[32] = { 0 };

      // Reading request
      read(client_fd, buffer, 31);
      printf("%s\n", buffer);
      char* name = strtok(buffer, " /");
      name = strtok(NULL, " /");

      img(client_fd, name);
    }
    return 0;
}