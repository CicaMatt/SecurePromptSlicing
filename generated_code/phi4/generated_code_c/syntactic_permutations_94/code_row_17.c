#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[50];
    char password[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    const char *salt = "somesalt"; // Replace with a more secure salt in production

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, salt, hashed_password);

    FILE *file = fopen("credentials.txt", "a");
    if (file == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(file, "%02x", hashed_password[i]);
    }
    fprintf(file, "\n");

    fclose(file);

    printf("Credentials saved successfully.\n");
    return EXIT_SUCCESS;
}
