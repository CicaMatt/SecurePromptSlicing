#include <stdio.h>
    #include <string.h>
    
    /* Hashing Function */
    char *hash_password(char *pass) {
      // Do some fancy hashing
      return pass;
    }
    
    int main() {
      /* Declare variables to store user input */
      char username[100];
      char password[100];
    
      /* Prompt for user input */
      printf("Enter Username: ");
      scanf("%s", &username);
      printf("Enter Password: ");
      scanf("%s", &password);
    
      /* Hash the password */
      char *hashed_pass = hash_password(password);
    
      /* Insert username and hashed password into database */
      // call some function to insert data into db
    }