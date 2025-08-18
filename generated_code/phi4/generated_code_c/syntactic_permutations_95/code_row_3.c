#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USERNAME];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char salt[16]; // 128-bit salt
} User;

void generate_salt(unsigned char *salt) {
    for (int i = 0; i < sizeof(salt); i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash_output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, sizeof(salt));
    SHA256_Final(hash_output, &sha256);
}

void register_user(User *user_db[], int *count, const char *username, const char *password) {
    User user;
    strcpy(user.username, username);

    generate_salt(user.salt);
    hash_password(password, user.salt, user.hash);

    user_db[*count] = (User *)malloc(sizeof(User));
    memcpy(user_db[(*count)], &user, sizeof(User));
    (*count)++;
}

int verify_user(const User *user_db[], int count, const char *username, const char *password) {
    for (int i = 0; i < count; i++) {
        if (strcmp(username, user_db[i]->username) == 0) {
            unsigned char hash_output[SHA256_DIGEST_LENGTH];
            hash_password(password, user_db[i]->salt, hash_output);
            if (memcmp(hash_output, user_db[i]->hash, SHA256_DIGEST_LENGTH) == 0) {
                return 1; // Password matches
            }
        }
    }
    return 0; // User not found or password does not match
}

int main() {
    srand(time(NULL));
    
    const int MAX_USERS = 10;
    User *user_db[MAX_USERS];
    int user_count = 0;

    char username[MAX_USERNAME], password[MAX_PASSWORD];

    printf("Register a new user:\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    register_user(user_db, &user_count, username, password);

    printf("\nEnter your credentials to login:\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (verify_user(user_db, user_count, username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    for (int i = 0; i < user_count; i++) {
        free(user_db[i]);
    }

    return 0;
}