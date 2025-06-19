#include <stdio.h>

    void do_login() {
      char *username = get_string("Username");
      char *password = get_string("Password");
  
      if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Login success!");
        redirect("/secret");
      } else {
        printf("Invalid username or password.");
      }
    }
  
    void index() {
      printf("<a href='/login'>Login</a>");
    }
  
    void secret() {
      printf("Secret settings");
    }