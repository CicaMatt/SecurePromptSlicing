#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define HASHED_PASS_LEN 64

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing function (for demonstration purposes only)
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    snprintf(hashed_password, HASHED_PASS_LEN, "%lu", hash);
}

void register_user(const char *username, const char *password) {
    char hashed_password[HASHED_PASS_LEN];

    // Hash the password
    hash_password(password, hashed_password);

    // In a real application, you would insert into a database.
    // For demonstration purposes, we'll just print it to stdout.

    printf("Registering user:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    // Simulate storing in a file (as an example of persistent storage)
    FILE *file = fopen("user_data.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s,%s\n", username, hashed_password);
        fclose(file);
    } else {
        perror("Failed to open user_data.txt");
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LEN, stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LEN, stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    register_user(username, password);

    return 0;
}