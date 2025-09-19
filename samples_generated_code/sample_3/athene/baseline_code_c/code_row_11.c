#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[HASH_SIZE];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(output, hash, HASH_SIZE);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hashed_password[HASH_SIZE + SALT_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    
    hash_password(password, salt, hashed_password);
    
    memcpy(hashed_password + HASH_SIZE, salt, SALT_SIZE);

    // Simulate storing in database
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        return 1;
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    printf("Registration successful!\n");

    return 0;
}