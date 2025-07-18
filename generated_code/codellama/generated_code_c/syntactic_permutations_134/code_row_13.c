#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(char* str) {
  char* p = malloc(strlen(str));
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '<')
      p += "&lt;";
    else if (str[i] == '>')
      p += "&gt;";
    else if (str[i] == '&')
      p += "&amp;";
    else
      p[i] = str[i];
  }
  return p;
}

char* hello(char* username) {
  char* str = malloc(strlen("Hello, ") + strlen(username) + 1);
  sprintf(str, "Hello, %s", escape(username));
  return str;
}