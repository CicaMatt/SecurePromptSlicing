#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN (SHA256_DIGEST_LENGTH * 2)
#define DB_ENTRY_SIZE (USERNAME_LEN + HASH_LEN + SALT_LEN)

void generate_salt(char *salt, int length) {
    for (int i = 0; i < length; i++) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha_hash[SHA256_DIGEST_LENGTH];
    char salted_password[PASSWORD_LEN + SALT_LEN];

    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256((unsigned char *)salted_password, strlen(salted_password), sha_hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", sha_hash[i]);
    }
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LEN + 1];
    char hash[HASH_LEN + 1];
    char db_entry[DB_ENTRY_SIZE + 1];

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hash);

    snprintf(db_entry, sizeof(db_entry), "%s:%s:%s", username, hash, salt);
    printf("Storing in DB: %s\n", db_entry); // Simulate storing in a database
}

int verify_password(const char *username, const char *password) {
    // This is a mockup of retrieving data from the database
    const char *db_entry = "testuser:5e884898da28047151d0e56f8dc6292773603d0d6aabbddc2b11abf3:aabbccdd";
    char stored_username[USERNAME_LEN + 1];
    char stored_hash[HASH_LEN + 1];
    char stored_salt[SALT_LEN + 1];

    sscanf(db_entry, "%[^:]:%[^:]:%s", stored_username, stored_hash, stored_salt);

    if (strcmp(username, stored_username) != 0) {
        return 0;
    }

    char hash_to_check[HASH_LEN + 1];
    hash_password(password, stored_salt, hash_to_check);

    return strcmp(hash_to_check, stored_hash) == 0;
}

int main() {
    srand(time(NULL));

    const char *username = "testuser";
    const char *password = "testpass";

    register_user(username, password);

    if (verify_password("testuser", "testpass")) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }

    return 0;
}