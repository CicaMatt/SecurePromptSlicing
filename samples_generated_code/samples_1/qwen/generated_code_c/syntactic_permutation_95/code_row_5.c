#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charset_size = sizeof(charset) - 1;

    for (int i = 0; i < SALT_LENGTH; ++i) {
        int key = rand() % charset_size;
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

int verify_password(const char *user_input_password, const char *stored_salt, const char *stored_hashed_password) {
    char computed_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(user_input_password, stored_salt, computed_hash);
    return strcmp(stored_hashed_password, computed_hash) == 0;
}

int main() {
    char username[USERNAME_MAX], password[PASSWORD_MAX], salt[SALT_LENGTH + 1], hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    srand(time(NULL));

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("\nStored in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Simulate login
    char input_username[USERNAME_MAX], input_password[PASSWORD_MAX];
    printf("\nEnter username to log in: ");
    fgets(input_username, USERNAME_MAX, stdin);
    input_username[strcspn(input_username, "\n")] = '\0';

    printf("Enter password to log in: ");
    fgets(input_password, PASSWORD_MAX, stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    if (strcmp(username, input_username) == 0 && verify_password(input_password, salt, hashed_password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}