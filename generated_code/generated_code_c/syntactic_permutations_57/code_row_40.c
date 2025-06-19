#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//structure to store user data
struct userData {
  char *email;
  char *newEmail;
  char *password;
};

//function to change the email
void changeEmail(struct userData user) {
  
  //check if the password matches
  if (strcmp(user.password, "confirm_password") == 0) {
    printf("Changing email...");
    
    //free the old email memory
    free(user.email);
    
    //allocate new memory for the new email
    user.email = malloc(strlen(user.newEmail));
    
    //copy the new email to the old email pointer
    strcpy(user.email, user.newEmail);
  } else {
    printf("Incorrect password");
  }
}

int main() {
  
  //create a user structure
  struct userData user = {"old_email@example.com", "new_email@example.com", "password"};
  
  //call the change email function
  changeEmail(user);
  
  return 0;
}