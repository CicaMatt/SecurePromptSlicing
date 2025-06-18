#include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #define MAX 100

    bool login(char *username, char *password) {
      printf("Enter your username: ");
      scanf("%s", username);
      printf("Enter your password: ");
      scanf("%s", password);
      if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        return true;
      } else {
        return false;
      }
    }

    void do_login() {
      char username[MAX];
      char password[MAX];
      if (login(username, password)) {
        printf("Login Successful!\n");
        admin_page();
      } else {
        printf("Invalid username or password.\n");
      }
    }

    void admin_page() {
      printf("Welcome to the admin page!\n");
    }