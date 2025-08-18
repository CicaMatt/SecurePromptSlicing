#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    char *input = malloc(strlen(password) + SALT_LENGTH + 1);
    strcpy(input, password);
    strcat(input, salt);

    SHA1((unsigned char *)input, strlen(input), digest);
    free(input);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[50];
    char password[50];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    salt[SALT_LENGTH] = '\0';

    hash_password(password, salt, hashed_password);
    strcpy(hashed_password + HASH_LENGTH, salt);

    printf("Storing in database: %s:%s\n", username, hashed_password);

    return 0;
}