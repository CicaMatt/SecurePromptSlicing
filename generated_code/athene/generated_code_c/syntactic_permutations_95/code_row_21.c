#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_LENGTH 32

typedef struct {
    char username[MAX_USERNAME];
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

void generate_salt(unsigned char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hashed_password) {
    unsigned char input[MAX_PASSWORD + SALT_LENGTH];
    memcpy(input, password, strlen(password));
    memcpy(input + strlen(password), salt, SALT_LENGTH);
    SHA256(input, strlen(password) + SALT_LENGTH, hashed_password);
}

void store_user(const User *user) {
    FILE *file = fopen("users.db", "ab");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
}

int main() {
    srand(time(NULL));

    User user;
    printf("Enter username: ");
    scanf("%49s", user.username);

    char password[MAX_PASSWORD];
    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(user.salt);
    hash_password(password, user.salt, user.hashed_password);

    store_user(&user);

    printf("Registration successful!\n");
    return 0;
}