#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes
void generateSalt(char *salt, int length);
char* hashPassword(const char *password, const char *salt);

int main() {
    char username[50];
    char password[50];
    char salt[13]; // 8 characters for the salt + null terminator

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generateSalt(salt, 8);

    char *hashedPassword = hashPassword(password, salt);

    char storage[100];
    snprintf(storage, sizeof(storage), "%s:%s%s", username, hashedPassword, salt);
    
    printf("Stored in database: %s\n", storage);

    free(hashedPassword);
    return 0;
}

void generateSalt(char *salt, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length > sizeof(charset) - 1)
        length = sizeof(charset) - 1;

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

char* hashPassword(const char *password, const char *salt) {
    // This is a placeholder for an actual hashing function
    size_t len = strlen(password) + strlen(salt) + 1;
    char *hashed = (char*)malloc(len);
    
    snprintf(hashed, len, "%s%s", password, salt); // Simple concatenation as a "hash"
    
    return hashed;
}