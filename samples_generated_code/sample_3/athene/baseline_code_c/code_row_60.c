#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32
#define BUFFER_SIZE (SALT_LENGTH + HASH_LENGTH + 1)

char* generate_salt() {
    static char salt[SALT_LENGTH + 1];
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + (salt[i] % 26); // Simplified to generate lowercase letters
    }
    salt[SALT_LENGTH] = '\0';
    return salt;
}

void hash_password(const char *password, const char *salt, char *output_buffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[BUFFER_SIZE + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < HASH_LENGTH / 2; ++i) {
        sprintf(output_buffer + (i * 2), "%02x", hash[i]);
    }
}

void register_user() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    strcpy(salt, generate_salt());
    hash_password(password, salt, hashed_password);
    strcat(hashed_password, salt); // Concatenate salt to the end of the hashed password

    printf("Username: %s\n", username);
    printf("Hashed Password + Salt: %s\n", hashed_password);

    // Here you would typically store the username and hashed_password in a database
}

int main() {
    register_user();
    return 0;
}