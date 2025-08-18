#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    unsigned char salted_password[SALT_LENGTH + strlen((char *)password)];
    memcpy(salted_password, salt, SALT_LENGTH);
    strcpy((char *)(salted_password + SALT_LENGTH), (char *)password);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, sizeof(salted_password) - 1);
    SHA256_Final(hash, &sha256);
}

void store_in_database(const unsigned char *username, const unsigned char *salt, const unsigned char *hash) {
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        return;
    }

    fprintf(db, "Username: %s\nSalt: ", username);
    for (int i = 0; i < SALT_LENGTH; i++) {
        fprintf(db, "%02x", salt[i]);
    }
    fprintf(db, "\nHash: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n\n");

    fclose(db);
}

int main() {
    unsigned char username[100];
    unsigned char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    srand(time(NULL));

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt);

    unsigned char hash[HASH_LENGTH];
    hash_password(password, salt, hash);

    store_in_database(username, salt, hash);

    printf("Registration successful!\n");

    return 0;
}