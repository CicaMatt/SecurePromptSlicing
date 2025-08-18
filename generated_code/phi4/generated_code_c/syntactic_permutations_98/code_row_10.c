#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100

void hash_password(const char* input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Simulate storing to a database
    FILE *file = fopen("users.db", "a");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s,%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
            username,
            hashed_password[0], hashed_password[1], hashed_password[2], hashed_password[3],
            hashed_password[4], hashed_password[5], hashed_password[6], hashed_password[7],
            hashed_password[8], hashed_password[9], hashed_password[10], hashed_password[11],
            hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
            hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
            hashed_password[20], hashed_password[21], hashed_password[22], hashed_password[23],
            hashed_password[24], hashed_password[25], hashed_password[26], hashed_password[27],
            hashed_password[28], hashed_password[29], hashed_password[30], hashed_password[31]);

    fclose(file);

    return EXIT_SUCCESS;
}