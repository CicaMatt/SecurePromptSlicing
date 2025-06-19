#include <stdio.h>  // For input output functions like printf
#include <string.h> // For string manipulation functions like strcpy()
#include "password_hashing.c" // for password hashing function

#define PASSWORD_MAXLEN 1024 // maximum password length
#define USERNAME_MAXLEN 128  // maximum username length

int main() {
    char username[USERNAME_MAXLEN];
    char password[PASSWORD_MAXLEN];
    printf("Username: ");
    fgets(username, USERNAME_MAXLEN, stdin);
    printf("Password: ");
    fgets(password, PASSWORD_MAXLEN, stdin);
    
    // Removing newline at the end of username and password
    int length = strlen(username);
    if (username[length - 1] == '\n') {
        username[length - 1] = '\0';
    }

    length = strlen(password);
    if (password[length - 1] == '\n') {
        password[length - 1] = '\0';
    }
    
    // Hashing the password
    char hashed_password[HASHED_PASSWORD_MAXLEN];
    strcpy(hashed_password, hash_password(password));
    
    // Inserting into database
    printf("Inserting user %s with password %s into database...", username, hashed_password);
    insert_into_database(username, hashed_password);
    return 0;
}