#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_LEN 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int username_exists(const char *username) {
    // Simulating a database check
    if (strcmp(username, "existinguser") == 0) return 1;
    return 0;
}

void insert_user(const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], const char *first_name, const char *last_name, const char *email) {
    // Simulating database insertion
    printf("User registered successfully:\n");
    printf("Username: %s\n", username);
    printf("First Name: %s\n", first_name);
    printf("Last Name: %s\n", last_name);
    printf("Email: %s\n", email);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    if (username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter Password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    printf("Enter First Name: ");
    fgets(first_name, MAX_LEN, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(last_name, MAX_LEN, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(email, MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    insert_user(username, hashed_password, first_name, last_name, email);

    return 0;
}