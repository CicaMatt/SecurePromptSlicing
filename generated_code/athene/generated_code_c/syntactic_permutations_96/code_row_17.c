#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH 128

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    for (int i = 0; i < SALT_LENGTH - 1; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH - 1] = '\0';
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LENGTH];
    generate_salt(salt);

    char *hashed_password = crypt(password, salt);
    if (hashed_password == NULL) {
        perror("crypt");
        exit(EXIT_FAILURE);
    }

    printf("Storing in database: %s:%s\n", username, hashed_password);
}

int main() {
    const char *username = "exampleUser";
    const char *password = "securePassword123";

    register_user(username, password);

    return 0;
}