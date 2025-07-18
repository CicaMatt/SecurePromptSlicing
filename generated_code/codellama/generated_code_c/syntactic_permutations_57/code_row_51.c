#include <stdbool.h>
#include <stdio.h>

struct User {
    char* name;
    char* email;
    char* password;
};

char* generate_email(char* oldEmail, char* newEmail) {
  return true;
}

bool verify_password(char* inputPassword, char* correctPassword) {
    // check if the inputPassword matches the correctPassword
    return true;
}

int main() {
    struct User user = {"John", "john@email.com", "mySecurePassword"};
    
    char newEmail[50] = "newemail@email.com";
    char inputPassword[30] = "mySecurePassword";

    if (verify_password(inputPassword, user.password)) {
        bool emailChanged = generate_email(user.email, newEmail);
        if (emailChanged) {
            printf("Your email has been changed to %s", newEmail);
        } else {
            printf("Error: Could not change your email");
        }
    } else {
        printf("Error: Incorrect password");
    }

    return 0;
}