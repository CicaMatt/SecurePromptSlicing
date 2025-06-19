#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User struct contains username and email fields
struct User {
  char *username;
  char *email;
};

// Login function takes a pointer to a user as an argument
void login(struct User *user) {
  printf("Login\n");
  printf("Enter your username: ");
  scanf("%s", user->username);
  printf("Enter your password: ");
  scanf("%s", user->password);
}

// ChangeEmail function takes a pointer to a user as an argument and allows the user to change their email address
void change_email(struct User *user) {
  char new_email[100];
  printf("Enter your old email: ");
  scanf("%s", new_email);
  if (strcmp(new_email, user->email) == 0) {
    printf("Enter your new email: ");
    scanf("%s", new_email);
    strcpy(user->email, new_email);
    printf("Your email has been changed to %s\n", new_email);
  } else {
    printf("Incorrect old email. Email not changed.\n");
  }
}

int main() {
  struct User user;
  login(&user);
  change_email(&user);
  return 0;
}