#include <stdio.h>

void hello(char* name) {
  printf("Hello, %s!", escape(name));
}

int main() {
  char* username = "Joe";
  hello(username);
  return 0;
}