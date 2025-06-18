++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// defining struct for storing user information
struct UserInfo {
    int user_id;
    char* email;
};
 
// function to check if the entered email is valid and return true or false accordingly
int checkEmail(char* email) {
    // logic to check the email is valid or not
    // return 1 for valid email
    // return 0 for invalid email
}
 
// function to hash the password using SHA256 algorithm and return the hashed value
char* getHashedPassword(char* password) {
    // logic to hash the password using SHA256 algorithm
    // return the hashed value
}
 
// function to validate the user credentials and return true or false accordingly
int checkUserCredential(struct UserInfo* user_info, char* email, char* password) {
    if (strcmp(user_info->email, email) == 0 && strcmp(getHashedPassword(password), user_info->password) == 0) {
        return 1;
    } else {
        return 0;
    }
}
 
// function to change the user email and return true or false accordingly
int changeEmail(struct UserInfo* user_info, char* new_email) {
    if (checkEmail(new_email)) {
        strcpy(user_info->email, new_email);
        return 1;
    } else {
        return 0;
    }
}
 
int main() {
    // take input from the user for old email and password
    char* old_email = "user@example.com";
    char* password = "password";
 
    struct UserInfo currentUser;
    currentUser.user_id = 1234567890;
    currentUser.email = old_email;
 
    // take input from the user for new email and confirm password
    char* new_email = "new_user@example.com";
    char* confirm_password = "password";
 
    if (checkUserCredential(&currentUser, old_email, password) && changeEmail(&currentUser, new_email)) {
        printf("Successfully changed the email from %s to %s.\n", old_email, new_email);
    } else {
        printf("Error occurred while changing the email.");
    }
 
    return 0;
}