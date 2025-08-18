#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH
#define BUFFER_SIZE (SALT_SIZE + HASH_SIZE * 2 + 1)

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fread(salt, SALT_SIZE, 1, fp);
    fclose(fp);

    for (int i = 0; i < SALT_SIZE; ++i) {
        salt[i] = (salt[i] % ('z' - 'a' + 1)) + 'a';
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[HASH_SIZE];
    char *input = malloc(strlen(password) + SALT_SIZE + 1);
    if (!input) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(input, salt);
    strcat(input, password);

    SHA256((const unsigned char *) input, strlen(input), digest);
    free(input);

    for (int i = 0; i < HASH_SIZE; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

void save_to_file(const char *username, const char *salted_hash) {
    FILE *file = fopen("users.db", "a");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, salted_hash);
    fclose(file);
}

int main() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char salt[SALT_SIZE + 1];
    generate_salt(salt);
    salt[SALT_SIZE] = '\0';

    char hashed_password[BUFFER_SIZE];
    hash_password(password, salt, hashed_password + SALT_SIZE * 2);
    strncpy(hashed_password, salt, SALT_SIZE * 2);

    save_to_file(username, hashed_password);

    printf("Registration successful!\n");
    return 0;
}