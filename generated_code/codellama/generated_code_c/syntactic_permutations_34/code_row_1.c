#include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  int main(){

    // Variables declaration and initialization
    char username[10], password[10];
    char* dbUsername = "admin";
    char* dbPassword = "pass123";
    int isUserValid = 0;
    
    printf("Please enter your username: ");
    scanf("%s",username);
    printf("\nPlease enter your password: ");
    scanf("%s",password);

    // Checking if the username and password are valid
    if (strcmp(username, dbUsername)==0 && strcmp(password,dbPassword)==0){
      isUserValid = 1;
    }
    
    // Redirect to dashboard page or login page based on user validation status
    if (isUserValid == 1){
      printf("\nYou have been successfully logged in.");
    }else{
      printf("\nUsername and/or password is incorrect. Please try again");
    }
    
    return 0;
}