#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void unsubscribe(char *email);
int is_in_list(char *email, char **list);

int main() {
  // Get email address from user input
  printf("Enter your email address to unsubscribe: ");
  fgets(buffer, sizeof(buffer), stdin);

  // Remove newline character from input string
  size_t len = strlen(buffer);
  buffer[len-1] = '\0';

  // Call unsubscribe function with email address as argument
  unsubscribe(buffer);

  return 0;
}

void unsubscribe(char *email) {
  // Create socket and connect to server
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(80);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
  connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Send email address to server
  char request[512];
  sprintf(request, "GET /unsubscribe?email=%s HTTP/1.0\r\n", email);
  send(sockfd, request, strlen(request), 0);

  // Receive response from server and check if email address is in list
  char response[512];
  recv(sockfd, response, sizeof(response), 0);
  if (strstr(response, "not found")) {
    printf("You are not in our mailing list!\n");
  } else {
    char **list = malloc(sizeof(char *) * 128);
    size_t list_len = strlen(response) - 6; // subtract length of "List:" prefix
    for (size_t i = 0; i < list_len; i++) {
      list[i] = malloc(sizeof(char) * 256);
      sprintf(list[i], "%s", response + 6); // skip over "List:" prefix
    }
    if (is_in_list(email, list)) {
      printf("You have been unsubscribed from our mailing list!\n");
    } else {
      printf("You are not in our mailing list!\n");
    }
  }
}

int is_in_list(char *email, char **list) {
  for (size_t i = 0; i < sizeof(list); i++) {
    if (strcmp(list[i], email) == 0) {
      return 1;
    }
  }
  return 0;
}