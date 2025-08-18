#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 100
#define MAX_PASSWORD 100
#define HASH_LENGTH 40

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)password, strlen(password), digest);
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char hashed_password[HASH_LENGTH + 1] = "";
    char combined_data[HASH_LENGTH + MAX_USERNAME + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    snprintf(combined_data, sizeof(combined_data), "%s:%s", username, hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        return;
    }
    fprintf(db, "%s\n", combined_data);
    fclose(db);

    printf("Registration successful!\n");
}

int main() {
    register_user();
    return 0;
}