#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <syslog.h>
#include <signal.h>
#include <netdb.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <mqueue.h>
#include <sys/msg.h>
#include <signal.h>
#include <syslog.h>
#include "server_config.h"

// Set the upload directory path
char* UPLOAD_DIR = "./uploads";

void startServer(int port) {
  int sock;
  struct sockaddr_in server, client;
  int addrlen = sizeof(struct sockaddr_in);
  char buffer[1024];
  ssize_t bytes_read;

  // Create a socket for the server
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Server: socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the address and port
  if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
    perror("Server: bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(sock, 5) == -1) {
    perror("Server: listen failed");
    exit(EXIT_FAILURE);
  }

  while (1) {
    printf("Waiting for connection...\n");

    // Accept an incoming connection
    if ((client_fd = accept(sock, (struct sockaddr*)&client, (socklen_t*)&addrlen)) == -1) {
      perror("Server: accept failed");
      exit(EXIT_FAILURE);
    }

    // Read data from the client
    bytes_read = read(client_fd, buffer, 1024);
    if (bytes_read == -1) {
      perror("Server: read failed");
      exit(EXIT_FAILURE);
    }

    // Process the request and send a response back to the client
    processRequest(client_fd, buffer, bytes_read);
  }
}

void processRequest(int client_fd, char* buffer, ssize_t bytes_read) {
  int file_fd;
  char* filename = strtok(buffer, " ");
  char* filesize = strtok(NULL, " ");
  char* upload_dir = UPLOAD_DIR;
  char* full_filename;
  char msg[1024];
  struct stat sbuf;

  // Check if the file already exists
  if (stat(full_filename, &sbuf) == -1) {
    perror("Server: stat failed");
    exit(EXIT_FAILURE);
  }

  // Create a new file in the upload directory
  full_filename = malloc(strlen(upload_dir) + strlen(filename));
  sprintf(full_filename, "%s/%s", upload_dir, filename);

  if ((file_fd = open(full_filename, O_WRONLY | O_CREAT | O_EXCL)) == -1) {
    perror("Server: open failed");
    exit(EXIT_FAILURE);
  }

  // Send a success message to the client
  sprintf(msg, "File %s uploaded successfully!", filename);
  send(client_fd, msg, strlen(msg), 0);

  // Read data from the client and write it to the file
  while (bytes_read > 0) {
    if ((write(file_fd, buffer, bytes_read)) == -1) {
      perror("Server: write failed");
      exit(EXIT_FAILURE);
    }
    bytes_read = read(client_fd, buffer, 1024);
  }

  // Close the file and socket
  close(file_fd);
  close(client_fd);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  startServer(atoi(argv[1]));

  return 0;
}

### Explanation:
The code generates a web server in C language. The server listens for incoming connections on the specified port and accepts them. When a client connects, it reads data from the client and sends a response back to the client. The response includes a success message and the number of bytes read. The data is then written to a file in the upload directory. The file is created using the open() function with the O_WRONLY, O_CREAT, and O_EXCL flags. The write() function is used to write data to the file, and the close() function is used to close the file and socket.