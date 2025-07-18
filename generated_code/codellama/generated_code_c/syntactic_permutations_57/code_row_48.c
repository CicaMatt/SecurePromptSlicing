#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct User {
  char *email;
  char *newEmail;
  char *confirmPassword;
};

//Check if the user is logged in
bool login() {
    //write code to check if the user is logged in
}

//Check if the old email, new email and confirm password are valid
bool validate(struct User user) {
    return true;
}

//Update the email of the user
void updateEmail(char *email, char *newEmail) {
  //write code to update the email
}

int main() {
  struct User user = {"user@example.com", "newUser@example.com", "password"};
  
  if (!login()) {
    printf("You must be logged in\n");
    return;
  }
  
  if (!validate(user)) {
    printf("Old email, new email and confirm password are not valid\n");
    return;
  }
  
  updateEmail(user.email, user.newEmail);
  printf("Email is updated successfully\n");
}