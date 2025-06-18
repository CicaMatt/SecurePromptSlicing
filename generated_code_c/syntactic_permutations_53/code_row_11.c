#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    
    /* Login page */
    void login_page(void) {
      printf("Please enter your username: ");
      char* username = malloc(100);
      fgets(username, 100, stdin);
      printf("Please enter your password: ");
      char* password = malloc(100);
      fgets(password, 100, stdin);
    
      if (strcmp(username, "admin\n") == 0 && strcmp(password, "password123\n") == 0) {
        printf("Login successful! Redirecting to admin page...");
        admin_page();
      } else if (strcmp(username, "user\n") == 0 && strcmp(password, "password123\n") == 0) {
        printf("Login successful! Redirecting to user page...");
        user_page();
      } else {
        printf("Invalid credentials. Redirecting to login page...");
        login_page();
      }
    }
    
    /* User page */
    void user_page(void) {
      char* welcome = "Welcome, user!";
      printf("%s", welcome);
    }
    
    /* Admin page */
    void admin_page(void) {
      char* welcome = "Welcome, admin!";
      printf("%s", welcome);
    }
    
    int main(int argc, char** argv) {
      login_page();
      return 0;
    }