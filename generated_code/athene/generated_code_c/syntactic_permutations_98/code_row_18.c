#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    FILE *file = fopen("users.dat", "ab");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(username, sizeof(char), strlen(username), file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(hashed_password, sizeof(unsigned char), SHA256_DIGEST_LENGTH, file);
    fwrite("\n", sizeof(char), 1, file);

    fclose(file);

    printf("Registration successful!\n");

    return 0;
}