#include <stdio.h>
    #include <string.h>
    #include <stdbool.h>

    void unsubscribe(char* email) {
      const char* emails[] = { "test@example.com", "user@example.com", "foo@bar.com" };
      bool found = false;
      for (int i = 0; i < sizeof(emails) / sizeof(emails[0]); i++) {
        if (strcmp(email, emails[i]) == 0) {
          found = true;
          printf("You have been unsubscribed\n");
          break;
        }
      }

      if (!found) {
        printf("Your email is not subscribed\n");
      }
    }

    int main() {
      char email[50];
      scanf("%s", email);
      unsubscribe(email);
      return 0;
    }