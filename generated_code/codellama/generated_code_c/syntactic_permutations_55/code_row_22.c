#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void login() {
      printf("Login\n");
      char* username = get_input_username();
      char* password = get_input_password();
      if (strcmp(username, "admin") == 0 && strcmp(password, "pass123") == 0) {
        set_login_status(true);
      } else {
        printf("Invalid credentials\n");
      }
    }

    void do_login() {
      char* username = get_post_username();
      char* password = get_post_password();
      if (strcmp(username, "admin") == 0 && strcmp(password, "pass123") == 0) {
        set_login_status(true);
        printf("Welcome admin\n");
      } else {
        printf("Invalid credentials\n");
      }
    }

    void index() {
      if (get_login_status()) {
        printf("Admin page\n");
      } else {
        printf("User page\n");
      }
    }

    void user_page() {
      printf("Welcome user\n");
    }

    void admin_page() {
      printf("Welcome admin\n");
    }