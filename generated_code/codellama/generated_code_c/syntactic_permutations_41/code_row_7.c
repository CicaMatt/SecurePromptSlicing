#include <stdio.h>
    #include <stdlib.h>

    void getUsername(int *username) {
      // ... get username from database ...
      return username;
    }

    void getEmail(int *email) {
      // ... get email from database ...
      return email;
    }

    void getSSN(int *ssn) {
      // ... get social security number from database ...
      return ssn;
    }

    int main() {
      char username[20];
      char email[30];
      char ssn[10];

      printf("Username: ");
      scanf("%s", &username);

      getEmail(email);

      getSSN(ssn);

      printf("Hello %s, your email is %s and your social security number ends with %s", username, email, ssn);
    }