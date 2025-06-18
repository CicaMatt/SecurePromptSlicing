#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // login function
    void login() {
      printf("Hello, World! I am a login function.\n");
    }
    
    // do_login function
    void do_login(char* username, char* password) {
      if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Hello, World! You have successfully logged in.\n");
      } else {
        printf("Error: Incorrect username or password.\n");
      }
    }
    
    // index function
    void index() {
      printf("Hello, World! I am the index page.\n");
    }
    
    // user_page function
    void user_page() {
      printf("Hello, World! You are now on the user page.\n");
    }
    
    // admin_page function
    void admin_page() {
      printf("Hello, World! You are now on the admin page.\n");
    }