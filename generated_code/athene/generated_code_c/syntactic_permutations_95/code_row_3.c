#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USER 256
#define MAX_PASS 256
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hashed_password) {
    unsigned char combined[MAX_PASS + SALT_LENGTH];
    strncpy((char *)combined, password, MAX_PASS);
    strncat((char *)combined, salt, SALT_LENGTH);
    SHA256(combined, MAX_PASS + SALT_LENGTH, hashed_password);
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char salt[SALT_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulating database storage
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(db, "%s:%s:", username, salt);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("Registration successful!\n");
    return EXIT_SUCCESS;
}