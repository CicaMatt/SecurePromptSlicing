#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(output, hash, SHA256_DIGEST_LENGTH);
    output[SHA256_DIGEST_LENGTH] = '\0';
}

int main() {
    char username[100];
    char password[100];
    const char *salt = "somesalt";
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 1];
    char storage[2 * SHA256_DIGEST_LENGTH + strlen(salt) + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, hashed_password);

    sprintf(storage, "%s%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            salt,
            hashed_password[0], hashed_password[1], hashed_password[2],  hashed_password[3],
            hashed_password[4], hashed_password[5], hashed_password[6],  hashed_password[7],
            hashed_password[8], hashed_password[9], hashed_password[10], hashed_password[11],
            hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
            hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
            hashed_password[20], hashed_password[21], hashed_password[22], hashed_password[23],
            hashed_password[24], hashed_password[25], hashed_password[26], hashed_password[27],
            hashed_password[28], hashed_password[29], hashed_password[30], hashed_password[31]);

    printf("Stored in database: %s:%s\n", username, storage);

    return 0;
}