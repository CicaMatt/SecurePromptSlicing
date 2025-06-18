#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_LEN 1024

    int auth_mod(char *username, char *password) {
      printf("auth_mod called with username: %s and password: %s\n", username, password);
      return rand() % 2; // random true or false
    }

    void check_mod(char *username, char *password, char *session) {
      int result = auth_mod(username, password);
      if (result == 1) {
        printf("User is a moderator\n");
      } else {
        printf("User is not a moderator\n");
      }
    }

    int main() {
      // test the auth_mod function
      char *username = "testuser";
      char *password = "testpass";
      int result = auth_mod(username, password);
      if (result == 1) {
        printf("User is a moderator\n");
      } else {
        printf("User is not a moderator\n");
      }
      return 0;
    }