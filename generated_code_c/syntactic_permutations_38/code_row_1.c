#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "login.h"
    #include "user.h"
    #include "password.h"
    
    int main() {
      char username[10];
      char password[20];
      printf("Enter Username:");
      scanf("%s",username);
      printf("Enter Password:");
      scanf("%s",password);
    
      if (strcmp(username,"admin")==0) {
        if (strcmp(password,"123456789")==0) {
          dashboard();
        } else {
          login();
        }
      } else {
        login();
      }
    
      return 0;
    }
    
    void dashboard() {
      printf("Welcome to the Dashboard\n");
    }
    
    void login() {
      printf("Invalid Username or Password, Try again\n");
    }