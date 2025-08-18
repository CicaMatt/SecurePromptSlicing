#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USERNAME];
    char hashed_password_and_salt[256]; // Assuming a reasonable size for hash + salt
} User;

// Mock database as an array of users
User database[10];
int user_count = 0;

unsigned long generate_random_number() {
    return (unsigned long)time(NULL);
}

void generate_salt(char *salt, size_t length) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *output_hash) {
    // A very simple hash function for demonstration purposes
    unsigned long hash = generate_random_number();
    snprintf(output_hash, 256, "%lu%s", hash, salt);
}

int register_user(const char *username, const char *password) {
    if (user_count >= 10) {
        return -1; // Database full
    }

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            return -2; // Username already exists
        }
    }

    char salt[16];
    generate_salt(salt, sizeof(salt));

    char hashed_password_and_salt[256];
    hash_password(password, salt, hashed_password_and_salt);

    strcpy(database[user_count].username, username);
    strcpy(database[user_count].hashed_password_and_salt, hashed_password_and_salt);
    
    user_count++;
    return 0; // Success
}

int verify_user(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            char stored_salt[16];
            memcpy(stored_salt, database[i].hashed_password_and_salt + strlen(database[i].hashed_password_and_salt) - 15, sizeof(stored_salt));
            char input_hashed_password[256];
            hash_password(password, stored_salt, input_hashed_password);
            
            if (strcmp(input_hashed_password, database[i].hashed_password_and_salt) == 0) {
                return 1; // Password is correct
            }
            break;
        }
    }

    return -1; // User not found or password incorrect
}

int main() {
    srand((unsigned int)time(NULL));

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);

    int result = register_user(username, password);

    if (result == 0) {
        printf("Registration successful!\n");
    } else if (result == -1) {
        printf("Registration failed: Database is full.\n");
    } else if (result == -2) {
        printf("Registration failed: Username already exists.\n");
    }

    // For demonstration, try to verify the user immediately
    result = verify_user(username, password);
    
    if (result == 1) {
        printf("Login successful!\n");
    } else {
        printf("Login failed: User not found or password incorrect.\n");
    }

    return 0;
}