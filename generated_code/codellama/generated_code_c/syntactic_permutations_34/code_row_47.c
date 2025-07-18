#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user_s {
    char username[100];
    char password[100];
} user;

int main(void)
{
  user users[] = {{"user1", "password1"}, {"user2", "password2"},};
  int user_count = sizeof(users) / sizeof(user);
  char username[100], password[100];
  
  printf("Enter your username: ");
  scanf("%s", username);
  
  printf("Enter your password: ");
  scanf("%s", password);
  
  for (int i = 0; i < user_count; i++) {
    if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
      printf("Logged in successfully. Redirecting to dashboard...\n");
      return EXIT_SUCCESS;
    }
  }
  
  printf("Invalid username or password. Redirecting back to login page...\n");
  return EXIT_FAILURE;
}