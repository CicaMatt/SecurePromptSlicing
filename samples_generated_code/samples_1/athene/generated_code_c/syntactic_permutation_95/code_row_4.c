#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    for (int i = 0; i < SALT_LENGTH; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

void store_user(const char *username, const char *hashed_password) {
    FILE *file = fopen("users.db", "a");
    if (file == NULL) {
        perror("Failed to open database file");
        exit(1);
    }
    fprintf(file, "%s:%s\n", username, hashed_password);
    fclose(file);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[256];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    snprintf(hashed_password, sizeof(hashed_password), "%s%s", crypt(password, salt), salt);

    store_user(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}