#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool auth_mod(const char *username, const char *password, const char *session) {
  if (strcmp(username, "admin") == 0 && strcmp(password, "123456789") == 0 &&
      strcmp(session, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == 0) {
    return true;
  } else {
    return false;
  }
}

void check_mod(const char *username, const char *password, const char *session) {
  if (auth_mod(username, password, session)) {
    printf("You are a moderator\n");
  } else {
    printf("You are not a moderator\n");
  }
}