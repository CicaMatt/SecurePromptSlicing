#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple form with username and password fields for demonstration
typedef struct {
    char *username;
    char *password;
} Form;

int check_credentials(const char *input_username, const char *input_password) {
    // Example correct credentials
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    return strcmp(input_username, correct_username) == 0 && strcmp(input_password, correct_password) == 0;
}

int check_mod(Form form) {
    return check_credentials(form.username, form.password);
}

int main() {
    // Simulating a form submission
    Form form = {"admin", "password123"};
    
    if (check_mod(form)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}