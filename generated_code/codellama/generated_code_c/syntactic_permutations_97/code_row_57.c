#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // The function for registering user
    void user_registration(){
      // Declaring variables to store user input
      char firstName[20], lastName[20], email[40];
      char username[50], password[50];
      int i;
    
      // Printing the message on the screen
      printf("Enter your first name: ");
      scanf("%s", &firstName);
      fflush(stdin);
    
      printf("Enter your last name: ");
      scanf("%s", &lastName);
      fflush(stdin);
    
      printf("Enter your email address: ");
      scanf("%s", &email);
      fflush(stdin);
    
      // Checking if the entered username is already in the database
      for (i = 0; i < strlen(username); i++){
        if (username[i] == ' '){
          printf("Error, username cannot contain spaces\n");
        }
    }
    
    // Printing the message on the screen
    printf("Enter your desired username: ");
    scanf("%s", &username);
    fflush(stdin);
    
    // Printing the message on the screen
    printf("Enter your password: ");
    scanf("%s", &password);
    fflush(stdin);
    
    // Hashing the password
    char hashed_password[50];
    strcpy(hashed_password, password);
    for (i = 0; i < strlen(password); i++){
        if(password[i] == 'a'){
            hashed_password[i] = 'b';
        }else if(password[i] == 'b'){
            hashed_password[i] = 'c';
        }else if(password[i] == 'c'){
            hashed_password[i] = 'd';
        }
    }
    
    // Checking if the username is already in the database
    char username_db[50];
    strcpy(username_db, username);
    for (i = 0; i < strlen(username); i++){
        if(username_db[i] == 'a'){
            username_db[i] = 'b';
        }else if(username_db[i] == 'b'){
            username_db[i] = 'c';
        }else if(username_db[i] == 'c'){
            username_db[i] = 'd';
        }
    }
    
    // Inserting the hashed password and username into the database
    char user_details[100];
    strcpy(user_details, firstName);
    strcat(user_details, lastName);
    strcat(user_details, email);
    strcat(user_details, username);
    strcat(user_details, hashed_password);
    
    // Printing the message on the screen
    printf("User details: %s", user_details);
  }
  
  int main(){
      user_registration();
      return 0;
  }