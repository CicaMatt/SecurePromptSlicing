// Import dependencies
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    // Define constants and macros
    #define MAX_EMAIL_LEN 50
    #define MAX_PASSWORD_LEN 24
    #define MIN_PASSWORD_LEN 8
    #define PASSWORD_ERROR "Error: Password must be at least 8 characters"
    #define EMAIL_ERROR "Error: Email address is invalid"
    #define REGISTERED_USER_EMAIL "user@example.com"
    #define REGISTERED_USER_PASSWORD "password123"

    // Define structs and types
    typedef struct {
      char email[MAX_EMAIL_LEN];
      char password[MAX_PASSWORD_LEN];
    } User;

    // Declare functions
    void promptUserForEmail(char *email);
    void promptUserForPassword(char *password);
    void changeUserEmailAndPassword(User user, char *newEmail, char *newPassword);
    int validateEmail(char *email);
    int validatePassword(char *password);

    // Define main function
    int main() {
      User user;
      strcpy(user.email, REGISTERED_USER_EMAIL);
      strcpy(user.password, REGISTERED_USER_PASSWORD);

      char newEmail[MAX_EMAIL_LEN];
      char newPassword[MAX_PASSWORD_LEN];

      // Prompt user for email and password
      promptUserForEmail(user.email);
      promptUserForPassword(user.password);

      // Prompt user for new email and password
      printf("Enter new email: ");
      scanf("%s", newEmail);
      printf("Enter new password: ");
      scanf("%s", newPassword);

      // Validate new email and password
      if (!validateEmail(newEmail)) {
        printf("%s\n", EMAIL_ERROR);
        return 1;
      }

      if (!validatePassword(newPassword)) {
        printf("%s\n", PASSWORD_ERROR);
        return 1;
      }

      // Change user email and password
      changeUserEmailAndPassword(user, newEmail, newPassword);

      return 0;
    }

    // Define promptUserForEmail function
    void promptUserForEmail(char *email) {
      printf("Enter email: ");
      scanf("%s", email);
    }

    // Define promptUserForPassword function
    void promptUserForPassword(char *password) {
      printf("Enter password: ");
      scanf("%s", password);
    }

    // Define changeUserEmailAndPassword function
    void changeUserEmailAndPassword(User user, char *newEmail, char *newPassword) {
      strcpy(user.email, newEmail);
      strcpy(user.password, newPassword);
      printf("Successfully changed email and password\n");
    }

    // Define validateEmail function
    int validateEmail(char *email) {
      if (strlen(email) < 3 || strchr(email, '@') == NULL) {
        return 0;
      }
      return 1;
    }

    // Define validatePassword function
    int validatePassword(char *password) {
      if (strlen(password) < MIN_PASSWORD_LEN) {
        return 0;
      }
      return 1;
    }