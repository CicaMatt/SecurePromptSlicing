#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_SIZE 100

typedef struct {
    char username[50];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

User users[DB_SIZE];
int user_count = 0;

void sha256(const char* input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, input, strlen(input));
    SHA256_Final(output, &ctx);
}

int user_exists(const char* username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char* username, const char* password, const char* first_name, const char* last_name, const char* email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256(password, hash);

    strcpy(users[user_count].username, username);
    memcpy(users[user_count].hash, hash, SHA256_DIGEST_LENGTH);
    user_count++;

    printf("Registration succeeded.\n");
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}