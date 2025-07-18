#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hello(char* username) {
  printf("Hello %s", username);
}

int main() {
  char* username = "Ram";
  hello(username);
  return 0;
}