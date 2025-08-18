#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_BUFFER 256

typedef struct {
    char username[MAX_BUFFER];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

int connect_to_database() {
    // Simulated database connection function
    return 1; // Return 1 if connected successfully, otherwise 0
}

int check_user_exists(const char* username) {
    // Simulate checking the database for an existing user
    // Here we just assume no users exist yet
    return 0;
}

int insert_user_into_database(User user) {
    // Simulate inserting a user into the database
    printf("User %s registered successfully.\n", user.username);
    return 1; // Return 1 if insertion is successful, otherwise 0
}

void hash_password(const char* password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    User new_user;
    
    printf("Enter username: ");
    if (fgets(new_user.username, MAX_BUFFER, stdin) == NULL) return 1;
    new_user.username[strcspn(new_user.username, "\n")] = '\0';

    if (!connect_to_database()) {
        fprintf(stderr, "Failed to connect to the database.\n");
        return 1;
    }

    if (check_user_exists(new_user.username)) {
        printf("Username already exists. Please choose a different username.\n");
        return 1;
    }

    char password[MAX_BUFFER];
    printf("Enter password: ");
    if (fgets(password, MAX_BUFFER, stdin) == NULL) return 1;
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, new_user.hashed_password);

    char first_name[MAX_BUFFER], last_name[MAX_BUFFER], email[MAX_BUFFER];

    printf("Enter first name: ");
    if (fgets(first_name, MAX_BUFFER, stdin) == NULL) return 1;
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter last name: ");
    if (fgets(last_name, MAX_BUFFER, stdin) == NULL) return 1;
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter email: ");
    if (fgets(email, MAX_BUFFER, stdin) == NULL) return 1;
    email[strcspn(email, "\n")] = '\0';

    if (!insert_user_into_database(new_user)) {
        fprintf(stderr, "Failed to register the user.\n");
        return 1;
    }

    printf("Registration succeeded!\n");

    return 0;
}


To compile and run this code, make sure you have OpenSSL installed and linked during compilation. You can use a command like:


gcc -o registration registration.c -lcrypto
./registration