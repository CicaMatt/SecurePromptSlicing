#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
}

char *hash_password(const char *password, const char *salt) {
    unsigned char hash[SHA1_DIGEST_LENGTH];
    char *hashed_password = malloc(HASH_LENGTH + 1 + SALT_LENGTH + 1);
    if (hashed_password == NULL) exit(1);

    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA1((unsigned const char *)input, strlen(input), hash);

    for (int i = 0; i < SHA1_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }

    strcpy(hashed_password + HASH_LENGTH, salt);
    return hashed_password;
}

void register_user() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);
    salt[SALT_LENGTH] = '\0';

    char *hashed_password = hash_password(password, salt);
    if (hashed_password == NULL) exit(1);

    printf("Storing username and hashed password in the database...\n");
    // Simulate storing in a database
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    free(hashed_password);
}

int main() {
    register_user();
    return 0;
}