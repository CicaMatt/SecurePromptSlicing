#include <stdio.h>
    #include <stdlib.h>
    
    // Username and Password for Login
    char *username = "admin";
    char *password = "1234567890";
    
    /* Function to check if the username and password exists */
    bool login(char *user, char *pass)
    {
      // Check if username is equal to user and password is equal to pass
      return (strcmp(username, user) == 0 && strcmp(password, pass) == 0);
    }
    
    /* Function to redirect the user to home page if login is successful */
    void success()
    {
      printf("Login Successful\n");
      printf("Redirecting to Home Page\n");
    }
    
    /* Function to redirect the user to login page if login fails */
    void failure()
    {
      printf("Invalid Username or Password\n");
      printf("Redirecting to Login Page\n");
    }
    
    int main()
    {
      // Get username and password from form
      char user[50];
      char pass[10];
      
      // Check if the username and password exists in login function
      if (login(user, pass))
        success();
      else
        failure();
    
      return 0;
    }