#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

unsigned char* hash_password(const char* password) {
    unsigned char* digest = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);
    return digest;
}

int is_username_exists(const char* username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char* username, const char* password) {
    unsigned char* hashed_password = hash_password(password);
    
    strcpy(users[user_count].username, username);
    memcpy(users[user_count].hashed_password, hashed_password, SHA256_DIGEST_LENGTH);

    user_count++;
    free(hashed_password);
}

int main() {
    char username[50];
    char password[50];
    char first_name[50];
    char last_name[50];
    char email[100];

    printf("Enter first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    if (is_username_exists(username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        printf("Enter email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0';

        register_user(username, password);
        printf("Registration succeeded.\n");
    }

    return 0;
}