#include <stdio.h>
#include <string.h>
#include<conio.h>
#include<stdlib.h>

#define MAX_EMAILS 10
#define PASSWORD_LENGTH 256
#define EMAIL_LENGTH 100

/*Struct to store users*/
struct user{
    char email[EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
};

/*Global variable that stores all the registered users*/
struct user registered_users[MAX_EMAILS] = {
  {"JohnDoe@example.com", "password123"},
  {"JaneDoe@example.com", "password456"},
  {"BobSmith@example.com", "password789"},
};

/*Function to get user input*/
void get_input(char *str, char *prompt){
    printf("%s: ", prompt);
    fgets(str, PASSWORD_LENGTH, stdin);
}

/*Function to verify user email*/
int is_email_valid(char *email){
  int i;
  for (i=0; i < MAX_EMAILS; ++i){
      if( strcmp(registered_users[i].email, email) == 0 )
          return 1;
  }
  return 0;
}

/*Function to verify user password*/
int is_password_valid(char *password, char *email){
    int i;
    for (i=0; i < MAX_EMAILS; ++i){
        if( strcmp(registered_users[i].email, email) == 0 &&
            strcmp(registered_users[i].password, password) == 0 )
            return 1;
    }
    return 0;
}

/*Function to change user email*/
int change_user_email(char *old_email, char *new_email, char *confirm_password){
    int i;
    for (i=0; i < MAX_EMAILS; ++i){
        if( strcmp(registered_users[i].email, old_email) == 0 &&
            strcmp(registered_users[i].password, confirm_password) == 0 ){
                //Change the user email in registered users array.
                strcpy(registered_users[i].email, new_email);
                return 1;
        }
    }
    return 0;
}

int main() {
    char old_email[EMAIL_LENGTH];
    char new_email[EMAIL_LENGTH];
    char confirm_password[PASSWORD_LENGTH];
    int is_valid = 0;
    
    /*Get the user input*/
    get_input(old_email, "Enter your old email");
    get_input(new_email, "Enter your new email");
    get_input(confirm_password, "Enter your password to verify");
    
    //Check if user email is valid.
    is_valid = is_email_valid(old_email);
    if(!is_valid){
        printf("Invalid old email\n");
        return 1;
    }
    
    //Check if the confirm password matches the password for the given email.
    is_valid = is_password_valid(confirm_password, old_email);
    if(!is_valid){
        printf("Invalid password\n");
        return 1;
    }
    
    //Change user email in registered users array.
    change_user_email(old_email, new_email, confirm_password);
    printf("Email updated successfully\n");
    return 0;
}