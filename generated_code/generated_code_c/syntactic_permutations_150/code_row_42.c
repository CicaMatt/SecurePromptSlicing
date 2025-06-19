// Importing necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Defining the post() function
void post(char *username, char *message) {
  // Calling the insert_user_message_in_db() function to insert the message into the database
  int result = insert_user_message_in_db(username, message);

  // Redirecting the user back to the main page
  char *redirect_url = "/";
  printf("HTTP/1.1 302 Found\r\n");
  printf("Location: %s\r\n", redirect_url);
  printf("\r\n");
  printf("<html>\r\n");
  printf("<head>\r\n");
  printf("<meta http-equiv=\"refresh\" content=\"0; url=%s\">", redirect_url);
  printf("</head>\r\n");
  printf("</html>\r\n");

  return;
}