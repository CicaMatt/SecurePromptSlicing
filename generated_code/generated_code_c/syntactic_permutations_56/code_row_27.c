#include <stdio.h>
    #include <string.h>

    struct User {
      char* name;
      char* password;
      char* email;
    };

    void changeEmail(struct User *user, char *newEmail) {
      if (strcmp(user->email, newEmail) != 0) {
        user->email = newEmail;
      }
    }

    int main() {
      struct User user = {"John Doe", "password123", "johndoe@example.com"};
      char *newEmail = "janedoe@example.com";

      changeEmail(&user, newEmail);

      printf("User %s has changed their email to: %s\n", user.name, user.email);
    }