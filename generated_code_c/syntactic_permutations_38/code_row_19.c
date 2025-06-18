#include <stdio.h>
    #include <stdlib.h>
    #include "loginpage.h"
    
    int main() {
      printf("Please enter your username and password\n");
      char username[100];
      char password[100];
      scanf("%s", &username);
      scanf("%s", &password);
    
      if (username == "admin" && password == "admin") {
        printf("You have successfully logged in\n");
        redirectToDashboard();
      } else {
        printf("Invalid username and password. Please try again.\n");
        loginPage();
      }
      return 0;
    }