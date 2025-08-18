#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_len, unsigned char *hash_output) {
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    
    SHA512_Update(&sha512, password, strlen(password));
    SHA512_Update(&sha512, salt, salt_len);

    SHA512_Final(hash_output, &sha512);
}

int main() {
    srand(time(NULL));

    const char *db_file = "user_db.txt";
    FILE *file = fopen(db_file, "a+");
    if (!file) {
        perror("Failed to open the database file");
        return EXIT_FAILURE;
    }

    char username[50];
    char password[50];
    
    printf("Enter username: ");
    scanf("%49s", username);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hash_output[SHA512_DIGEST_LENGTH];
    hash_password(password, salt, SALT_SIZE, hash_output);

    fprintf(file, "%s:%.*s:", username, (int)SALT_SIZE, salt);
    for (size_t i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        fprintf(file, "%02x", hash_output[i]);
    }
    fprintf(file, "\n");

    fclose(file);

    // Simulate login process
    printf("\nEnter username to login: ");
    scanf("%49s", username);

    file = fopen(db_file, "r");
    if (!file) {
        perror("Failed to open the database file for reading");
        return EXIT_FAILURE;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *username_start = strtok(line, ":");
        char *salt_str = strtok(NULL, ":");
        if (strcmp(username_start, username) == 0) {
            unsigned char stored_salt[SALT_SIZE], stored_hash[SHA512_DIGEST_LENGTH];
            for (size_t i = 0; i < SALT_SIZE; ++i) {
                sscanf(salt_str + i * 2, "%2hhx", &stored_salt[i]);
            }
            const char *hash_hex = strtok(NULL, "\n");
            for (size_t i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
                sscanf(hash_hex + i * 2, "%2hhx", &stored_hash[i]);
            }

            unsigned char login_hash[SHA512_DIGEST_LENGTH];
            hash_password(password, stored_salt, SALT_SIZE, login_hash);

            if (memcmp(login_hash, stored_hash, SHA512_DIGEST_LENGTH) == 0) {
                printf("Login successful!\n");
            } else {
                printf("Invalid password.\n");
            }
            break;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}