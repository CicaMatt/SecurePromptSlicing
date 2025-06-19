#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int do_login(char *username, char *password) {
  if (strcmp(username, "admin") == 0 && strcmp(password, "password123")) {
    session_set("username", username);
    return 1;
  }
  return 0;
}

void index() {
  printf("<a href='login.php'>Login</a>");
}

void login(char *username, char *password) {
  if (do_login(username, password)) {
    redirect("secret.php");
  } else {
    printf("Invalid username or password!");
  }
}

void secret() {
  printf("<p>Secret settings</p>");
}