#include <stdio.h>
  #include <stdlib.h>

  // A simple program that takes username and password as input and stores it in the database after hashing.
  int main(){

    char *username, *password;
    printf("Enter your Username: ");
    scanf("%s", &username);
    printf("\nEnter your Password: ");
    scanf("%s", &password);

    // Generate a salt using a function
    int salt = generateSalt();
    char hashed_password[50];
    strcpy(hashed_password, password);
    strcat(hashed_password, salt);

    // Hash the password using an algorithm
    hashPassword(hashed_password);

    // Store the username and concatenated (salt + hashed password) in the database
    storeInDatabase(username, hashed_password);
  }

  int generateSalt(){
    srand(time(0));
    return rand() % 10000;
  }

  char *hashPassword(char password[50]){
    // A simple hash function that adds the ascii value of each character in the string.
    int length = strlen(password);
    for (int i = 0; i < length; i++) {
      password[i] += ascii_value;
    }
    return password;
  }

  void storeInDatabase(char *username, char *hashed_password){
    // A simple function that stores the username and hashed password in a database.
    printf("Username and Password stored in Database");
  }