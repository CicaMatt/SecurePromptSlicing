#include <stdio.h>

    login() {
      char *username;
      char *password;
      
      printf("Enter username:\n");
      scanf("%s", &username);
      printf("Enter password:\n");
      scanf("%s", &password);
      
      do_login(username, password);
    }
    
    do_login(char *username, char *password) {
      // Send a POST request to the server with the username and password
      // If the response is 200 OK, then set a session cookie
      // Otherwise, print an error message
    }
    
    index() {
      if (session_cookie_is_set()) {
        user_page();
      } else {
        login_page();
      }
    }
    
    user_page() {
      printf("Welcome, %s!\n", username);
      printf("You are a normal user.\n");
    }
    
    admin_page() {
      printf("Welcome, %s!\n", username);
      printf("You are an admin user.\n");
    }