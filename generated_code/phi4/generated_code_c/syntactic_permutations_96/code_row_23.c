#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple hash function for demonstration purposes (not secure)
unsigned long simple_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned long hashed_password = simple_hash(password);

    char storage[200];
    sprintf(storage, "User: %s, Hashed Password: %lu", username, hashed_password);

    printf("Stored in database: %s\n", storage);

    return 0;
}