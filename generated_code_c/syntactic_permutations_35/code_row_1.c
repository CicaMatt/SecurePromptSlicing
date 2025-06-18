#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // login form
  printf("Enter username: ");
  char *username = malloc(100);
  scanf("%s", username);
  printf("\n");

  printf("Enter password: ");
  char *password = malloc(100);
  scanf("%s", password);
  printf("\n");

  // database
  int user_exists = 1;
  int pass_correct = 1;

  // login function
  if (user_exists == 1 && pass_correct == 1) {
    // redirect to home page
    printf("Redirecting to home page...\n");
  } else {
    // redirect to login page
    printf("Invalid username and password. Redirecting to login page...\n");
  }

  return 0;
}