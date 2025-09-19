#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef struct {
    char *username;
    unsigned char hash[HASH_SIZE];
} User;

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_SIZE, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    unsigned char salted_pass[256 + SALT_SIZE];
    snprintf((char *)salted_pass, sizeof(salted_pass), "%s%.*s", password, (int)SALT_SIZE, (const char *)salt);
    SHA256(salted_pass, strlen((const char*)salted_pass), hash);
}

void save_user_to_db(const User *user) {
    printf("Saving user to database:\n");
    printf("Username: %s\n", user->username);
    for(int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", user->hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    User user;
    user.username = strdup(username);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt);

    hash_password(password, salt, user.hash);

    save_user_to_db(&user);

    free(user.username);
    return 0;
}