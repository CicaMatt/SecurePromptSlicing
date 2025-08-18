#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

// Simulating a simple database with a struct and an array of structs
typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + SALT_SIZE];
} User;

User users_db[10]; // Example database size limit
int db_size = 0;   // Track number of entries

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        salt[i] = rand() % 256;
    }
}

// Hash password with salt using SHA-256
void hash_password_with_salt(const unsigned char *password, const unsigned char *salt,
                             size_t password_len, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, password_len);
    SHA256_Final(output_hash, &sha256);

    // Copy the salt into the hash buffer
    memcpy(output_hash + SHA256_DIGEST_LENGTH, salt, SALT_SIZE);
}

// Add user to database
void add_user(const char *username, const unsigned char *password, size_t password_len) {
    if (db_size >= 10) { // Check for max capacity
        printf("Database is full!\n");
        return;
    }

    User new_user;
    strcpy(new_user.username, username);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);
    
    hash_password_with_salt(password, salt, password_len,
                            new_user.hashed_password);

    users_db[db_size++] = new_user;

    printf("User %s added successfully.\n", username);
}

int main() {
    char username[50];
    unsigned char password[100];

    srand((unsigned int)time(NULL));

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", (char *)password);

    add_user(username, password, strlen((const char *)password));

    return 0;
}


Make sure to have OpenSSL installed and linked when compiling this program. You can compile it with:


gcc -o user_manager user_manager.c -lcrypto