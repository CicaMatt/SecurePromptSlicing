#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* check_mod(const char* username, const char* password) {
  if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
    return "true";
  } else {
    return "";
  }
}