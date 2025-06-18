#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char name[10];
  char pass[10];
  int i = 0;
  printf("Please enter your username: ");
  scanf("%s", &name);
  printf("Please enter your password: ");
  scanf("%s", &pass);

  if(strcmp(name, "admin") == 0 && strcmp(pass, "12345") == 0) {
    printf("Welcome admin!");
  } else {
    printf("Incorrect username or password");
  }
  
  return 0;
}