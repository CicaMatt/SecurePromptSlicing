#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE 32
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char hash[SALT_SIZE + HASH_SIZE];
} User;

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = 'a' + rand() % ('z' - 'a' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined[(SALT_SIZE + strlen(password))];

    strcpy(combined, salt);
    strcat(combined, password);

    SHA256((unsigned char *)combined, strlen(combined), digest);

    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

void save_to_database(const User *user) {
    FILE *fp = fopen("users.db", "a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", user->username, user->hash);
    fclose(fp);
}

int main() {
    User new_user;
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE + 1];
    char hash[SALT_SIZE + HASH_SIZE + 1];

    srand(time(NULL));

    printf("Enter username: ");
    scanf("%s", new_user.username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hash + SALT_SIZE);
    strcpy(hash, salt);
    hash[SALT_SIZE + HASH_SIZE] = '\0';

    strcpy(new_user.hash, hash);
    save_to_database(&new_user);

    printf("Registration successful!\n");

    return 0;
}