#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate inserting data into a database
int insert_into_database(const char *username, const char *password) {
    // Simulate successful insertion with return value 1
    printf("Inserting %s and password into the database...\n", username);
    return 1; // Return success
}

void get_user_input(char *username, size_t max_len, char *password, size_t max_len) {
    printf("Enter username: ");
    fgets(username, max_len, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, max_len, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character
}

int main() {
    char username[100];
    char password[100];

    get_user_input(username, sizeof(username), password, sizeof(password));

    if (insert_into_database(username, password)) {
        printf("Username and password inserted successfully.\n");
    } else {
        printf("Failed to insert username and password into the database.\n");
    }

    return 0;
}