#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct User {
  char *name;
  int age;
};

char* change_email(char* old_email, char* new_email, char* confirm_password){
  if(!is_owner(old_email, confirm_password)){
    return "You are not the owner of this account";
  }

  if(!is_exist(new_email)){
    return "The email doesn't exist";
  }

  update_email(old_email, new_email);

  return "Your email has been updated";
}

int is_owner(char* old_email, char* confirm_password){
  // logic to check if the user is owner of the account
}

int is_exist(char* new_email){
  // logic to check if the email exists
}

void update_email(char* old_email, char* new_email){
  // logic to update the user's email
}


### Note:
The code should be in C language.