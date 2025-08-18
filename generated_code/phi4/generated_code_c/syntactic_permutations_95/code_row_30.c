#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SALT_LENGTH 16

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int index;
    for (int i = 0; i < SALT_LENGTH; i++) {
        srand((unsigned int)(time(NULL) + rand()));
        index = rand() % (sizeof(charset) - 1);
        salt[i] = charset[index];
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    // Simple hashing for demonstration (not secure)
    int len = strlen(password) + SALT_LENGTH;
    hashed_password[0] = '\0';

    for (int i = 0; password[i]; i++) {
        sprintf(hashed_password + strlen(hashed_password), "%02x", password[i]);
    }

    strcat(hashed_password, salt);
}

void store_credentials(const char *username, const char *hashed_password) {
    FILE *file = fopen("credentials.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, hashed_password);
    fclose(file);
}

void register_user() {
    char username[50];
    char password[50];
    char salt[SALT_LENGTH + 1];
    char hashed_password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    store_credentials(username, hashed_password);

    printf("Registration successful!\n");
}

int main() {
    register_user();
    return 0;
}