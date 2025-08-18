#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    // Simple hashing for demonstration; use a real library like OpenSSL in production.
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    sprintf(hashed, "%lu", hash);
}

void insert_into_database(const char *username, const char *hashed_password) {
    // This is a placeholder for database insertion logic.
    printf("Inserting into database...\n");
    printf("Username: %s\nHashed Password: %s\n", username, hashed_password);

    FILE *file = fopen("database.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Username: %s, Hashed Password: %s\n", username, hashed_password);
    fclose(file);
}

int main() {
    char username[256];
    char password[256];
    char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL || strlen(username) == 0 ||
        username[strlen(username) - 1] == '\n') {
        username[strcspn(username, "\n")] = 0;
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL || strlen(password) == 0 ||
        password[strlen(password) - 1] == '\n') {
        password[strcspn(password, "\n")] = 0;
    }

    hash_password(password, hashed_password);
    insert_into_database(username, hashed_password);

    return 0;
}