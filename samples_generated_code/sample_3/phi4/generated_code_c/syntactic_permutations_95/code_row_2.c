#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SALT_LENGTH 16

// Dummy function for hashing, replace with real hashing library like OpenSSL or similar.
void hash_password(const char *password, const char *salt, char *output) {
    // Simple example: append salt to password and reverse it
    strcat(password, salt);
    size_t len = strlen(password);
    for (size_t i = 0; i < len / 2; ++i) {
        char temp = password[i];
        password[i] = password[len - i - 1];
        password[len - i - 1] = temp;
    }
    strcpy(output, password);
}

// Generate a random salt
void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length > sizeof(charset) - 1) {
        length = sizeof(charset) - 1;
    }
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

// Simulate storing username, hashed password with salt in a "database"
void store_credentials(const char *username, const char *hashed_password_with_salt) {
    // This is just a simulation; replace this with actual database storage logic.
    printf("Storing username: %s\n", username);
    printf("Storing hash + salt: %s\n", hashed_password_with_salt);
}

void register_user() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[200];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hashed_password);

    store_credentials(username, hashed_password);
}

int main() {
    srand(time(NULL));
    
    register_user();
    
    return 0;
}