#include <stdio.h>
    #include <string.h>

    char username[100];
    char password[100];

    void do_login(char *username, char *password) {
      if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        set_session("username", username);
        redirect("/secret");
      } else {
        printf("Invalid credentials!");
      }
    }

    void index() {
      printf("<a href='/login'>Login</a>");
    }

    void secret() {
      char *username = get_session("username");
      if (username == NULL) {
        redirect("/");
      } else {
        printf("Secret settings for %s", username);
      }
    }