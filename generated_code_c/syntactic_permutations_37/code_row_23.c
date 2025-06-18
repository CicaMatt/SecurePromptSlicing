#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

char username[16];
char password[16];

void get_username();
void get_password();
void verify_user_data();
void redirect(char *url);
void login_successful();
void cant_login();
void internal_server_error();

int main() {
  // clear the buffers
  memset(&username, 0, sizeof(username));
  memset(&password, 0, sizeof(password));

  get_username();
  get_password();
  verify_user_data();

  return 0;
}

void get_username() {
  printf("Username: ");
  fgets(username, sizeof(username), stdin);

  if (strlen(username) <= 1) {
    exit(EXIT_FAILURE);
  }

  username[strcspn(username, "\n")] = 0;
}

void get_password() {
  printf("Password: ");
  fgets(password, sizeof(password), stdin);

  if (strlen(password) <= 1) {
    exit(EXIT_FAILURE);
  }

  password[strcspn(password, "\n")] = 0;
}

void verify_user_data() {
  // use the username and password to check if they are in the database
  int user_found = 1;

  if (user_found == 1) {
    login_successful();
  } else {
    cant_login();
  }
}

void redirect(char *url) {
  printf("HTTP/1.1 302 Found\r\n");
  printf("Location: %s\r\n", url);
  printf("\r\n");
}

void login_successful() {
  char url[64];
  sprintf(url, "http://localhost/login?result=success&user=%s", username);
  redirect(url);
}

void cant_login() {
  redirect("http://localhost/login?result=failed");
}

void internal_server_error() {
  printf("HTTP/1.1 500 Internal Server Error\r\n");
  printf("\r\n");
}