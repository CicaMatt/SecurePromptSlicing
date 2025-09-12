#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    // Simple hashing algorithm for demonstration purposes
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    sprintf(hashed, "%lx", hash);
}

void store_in_database(const char *username, const char *hashed_password) {
    // Simulate database storage
    printf("Storing username: %s and hashed password: %s\n", username, hashed_password);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char hashed_password[HASH_SIZE + 1];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    store_in_database(username, hashed_password);

    return 0;
}