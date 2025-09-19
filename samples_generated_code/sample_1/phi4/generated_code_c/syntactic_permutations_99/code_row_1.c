#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple hash function to demonstrate hashing (not secure)
unsigned long simple_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

// Simulating database insertion
void insert_into_database(const char *username, unsigned long hashed_password) {
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %lu\n", hashed_password);
    // Here you would use a real database API to store the data
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
    }

    unsigned long hashed_password = simple_hash(password);
    insert_into_database(username, hashed_password);

    return 0;
}