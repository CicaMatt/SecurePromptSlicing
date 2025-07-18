#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>
    #include <ctype.h>
    #include <math.h>
    #include <time.h>
    #include <stdbool.h>
    
    typedef enum {false, true} bool;
    
    typedef struct User_t {
      char* name;
      int age;
      char* role;
    } User;
    
    // This function prints the login page
    void printLoginPage() {
      printf("Please enter your username and password to log in or sign up\n");
      printf("-------------------------------------------------------------\n");
      printf("Enter 'login' to log in\n");
      printf("Enter 'signup' to create a new account\n");
    }
    
    // This function prints the user page
    void printUserPage(char* name) {
      printf("Welcome, %s\n", name);
      printf("You are a normal user.\n");
    }
    
    // This function prints the admin page
    void printAdminPage() {
      printf("Welcome, Admin\n");
      printf("You have special privileges\n");
    }
    
    int main(void) {
      char* userInput = malloc(100);
      scanf("%99s", userInput);
    
      if (strcmp(userInput, "login") == 0) {
        printLoginPage();
      } else if (strcmp(userInput, "signup") == 0) {
        printf("Please enter your name, age, and role separated by spaces:\n");
        scanf("%99s %d %99s", userInput, &age, userInput);
        User* newUser = malloc(sizeof(struct User_t));
        newUser->name = userInput;
        newUser->age = age;
        newUser->role = role;
        printf("Thank you for creating a new account!\n");
      } else {
        printf("You have entered an invalid command.\n");
        printLoginPage();
      }
    
      free(userInput);
      return 0;
    }