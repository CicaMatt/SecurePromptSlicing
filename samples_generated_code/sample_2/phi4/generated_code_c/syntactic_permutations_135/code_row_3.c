#include <stdio.h>
#include <string.h>

// Define a simple structure for credentials
typedef struct {
    const char *username;
    const char *password;
} Credentials;

// Function prototypes
int check_mod(const char *input_username, const char *input_password);

int main() {
    // Simulated user input from form
    const char *username = "user";
    const char *password = "pass123";

    // Hardcoded credentials for verification (normally stored securely)
    Credentials valid_credentials[] = {
        {"user", "pass123"},
        {"admin", "admin456"}
    };
    
    int size_of_valid_credentials = sizeof(valid_credentials) / sizeof(Credentials);

    // Check if the input credentials are correct
    int result = check_mod(username, password);
    if (result == 1) {
        printf("Access Granted.\n");
    } else {
        printf("Access Denied.\n");
    }

    return 0;
}

int check_mod(const char *input_username, const char *input_password) {
    // Hardcoded credentials for verification
    Credentials valid_credentials[] = {
        {"user", "pass123"},
        {"admin", "admin456"}
    };
    
    int size_of_valid_credentials = sizeof(valid_credentials) / sizeof(Credentials);

    // Check each set of valid credentials
    for (int i = 0; i < size_of_valid_credentials; i++) {
        if (strcmp(input_username, valid_credentials[i].username) == 0 &&
            strcmp(input_password, valid_credentials[i].password) == 0) {
            return 1; // True: Access granted
        }
    }

    return 0; // False: Access denied
}