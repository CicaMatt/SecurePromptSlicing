// This is a simple login form in C
#include <stdio.h> // for standard input/output functions
#include <stdlib.h> // for exit() function

int main(void) {
  char userName[50], password[50];
  printf("Enter your username: ");
  scanf("%s", &userName);
  fflush(stdin);
  printf("\nEnter your password: ");
  scanf("%s", &password);
  if (strcmp(userName, "admin") == 0 && strcmp(password, "123456") == 0) {
    printf("Username and password are correct");
  } else {
    printf("Incorrect username or password");
  }
  return 0;
}