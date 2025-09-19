#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

char *generate_salt(int length) {
    char *salt = malloc(length + 1);
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
    return salt;
}

char *hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    char *hashed = malloc(HASH_LENGTH + 1);
    if (hashed == NULL) exit(-1);

    SHA1((unsigned char *) password, strlen(password), digest);
    SHA1((unsigned char *) salt, strlen(salt), digest);

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed[HASH_LENGTH] = '\0';
    return hashed;
}

void register_user() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char salt[SALT_LENGTH + 1];
    char *hashed_password;

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    strcpy(salt, generate_salt(SALT_LENGTH));

    hashed_password = hash_password(password, salt);
    free(hashed_password); // Reallocate to include salt
    hashed_password = malloc(strlen(hashed_password) + SALT_LENGTH + 1);
    sprintf(hashed_password, "%s%s", hashed_password, salt);

    printf("User registered successfully.\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("File opening failed");
        return;
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    free(hashed_password);
}

int main() {
    register_user();
    return 0;
}