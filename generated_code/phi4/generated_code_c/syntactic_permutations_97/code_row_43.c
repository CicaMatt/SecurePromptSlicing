#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USERS 100

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

void hashPassword(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int usernameExists(User users[], int count, const char *username) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void saveUsersToFile(User users[], int count) {
    FILE *file = fopen(DB_FILE, "wb");
    if (!file) {
        perror("Unable to open file");
        exit(1);
    }
    fwrite(users, sizeof(User), count, file);
    fclose(file);
}

int loadUsersFromFile(User users[]) {
    FILE *file = fopen(DB_FILE, "rb");
    if (!file) {
        return 0;
    }

    int count = fread(users, sizeof(User), MAX_USERS, file);
    fclose(file);

    for (int i = 0; i < count; ++i) {
        users[i].hashed_password[32] = '\0'; // Ensure null-termination
    }
    return count;
}

void registerUser(User users[], int *userCount) {
    char username[50], password[50], firstName[50], lastName[50], email[100];
    
    printf("Enter first name: ");
    fgets(firstName, sizeof(firstName), stdin);
    firstName[strcspn(firstName, "\n")] = 0;

    printf("Enter last name: ");
    fgets(lastName, sizeof(lastName), stdin);
    lastName[strcspn(lastName, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter username: ");
    scanf("%49s", username);

    if (usernameExists(users, *userCount, username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%49s", password);
    
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashed_password);

    strcpy(users[*userCount].username, username);
    memcpy(users[*userCount].hashed_password, hashed_password, SHA256_DIGEST_LENGTH);

    (*userCount)++;
    saveUsersToFile(users, *userCount);
    printf("Registration succeeded.\n");
}

int main() {
    User users[MAX_USERS];
    int userCount = loadUsersFromFile(users);

    registerUser(users, &userCount);

    return 0;
}
