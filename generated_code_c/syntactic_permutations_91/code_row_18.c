/*
 * Includes all necessary dependencies, including the ones required to use SHA-256 encryption for hashing passwords.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Database connection and query functions
#include "database_utils.c"

/*
 * Structure to store user data.
 */
struct user_data {
    char name[50];
    unsigned char password[SHA256_DIGEST_LENGTH];
};

// Function that creates a hashed password from plaintext password and stores it in the structure
void create_password(unsigned char* password, struct user_data* data) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen((char*)password));
    SHA256_Final(data->password, &ctx);
}

// Function that registers a user by taking name and plaintext password as input and storing it in the database.
void register_user(struct user_data* data) {
    char insert_query[100];
    sprintf(insert_query, "INSERT INTO users (name, password) VALUES ('%s', '%s')", data->name, data->password);
    execute_query(insert_query);
}

// Driver code to test the application.
int main() {
    struct user_data data;
    char* name = "John Doe";
    char* password = "secret12345";
    strcpy(data.name, name);
    create_password((unsigned char*)password, &data);
    register_user(&data);
    return 0;
}