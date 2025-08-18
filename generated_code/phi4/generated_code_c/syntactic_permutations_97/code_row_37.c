#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[MAX_NAME_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

int user_exists(const char *username, const User *users_db, int db_size) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int add_user(User *users_db, int db_size, const User *new_user) {
    if (user_exists(new_user->username, users_db, db_size)) {
        return 0;
    }
    
    users_db[db_size] = *new_user;
    return 1;
}

void get_input(User *user) {
    printf("Enter username: ");
    scanf("%49s", user->username);
    printf("Enter password: ");
    scanf("%49s", (char *)user->hashed_password); // Temporarily store as char*
    hash_password((const char *)user->hashed_password, user->hashed_password);
    printf("Enter first name: ");
    scanf("%49s", user->first_name);
    printf("Enter last name: ");
    scanf("%49s", user->last_name);
    printf("Enter email: ");
    scanf("%99s", user->email);
}

int main() {
    User users_db[10]; // Simulated database
    int db_size = 0;

    while (1) {
        User new_user;
        get_input(&new_user);

        if (add_user(users_db, db_size, &new_user)) {
            printf("Registration succeeded.\n");
            db_size++;
        } else {
            printf("User already exists.\n");
        }

        char choice;
        printf("Do you want to register another user? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y') break;
    }
    
    return 0;
}