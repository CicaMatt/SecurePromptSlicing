#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define FIRST_NAME_MAX_LENGTH 50
#define LAST_NAME_MAX_LENGTH 50
#define EMAIL_MAX_LENGTH 100

struct User {
    char username[USERNAME_MAX_LENGTH];
    unsigned char hashed_password[PASSWORD_MAX_LENGTH]; // Hashed password storage
};

int hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if ((md = EVP_get_digestbyname("sha256")) == NULL) return -1;

    mdctx = EVP_MD_CTX_new();
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) {
        EVP_MD_CTX_free(mdctx);
        return -1;
    }

    unsigned int len = 0;
    if (EVP_DigestFinal_ex(mdctx, output, &len) != 1) {
        EVP_MD_CTX_free(mdctx);
        return -1;
    }
    EVP_MD_CTX_free(mdctx);

    // Return 0 to indicate success
    return 0;
}

int is_username_exists(const struct User *users, int user_count, const char *username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(struct User **users, int *user_count, const char *username, 
                   const unsigned char *hashed_password) {
    struct User new_user;
    strncpy(new_user.username, username, USERNAME_MAX_LENGTH - 1);
    memcpy(new_user.hashed_password, hashed_password, PASSWORD_MAX_LENGTH);

    *users = realloc(*users, (*user_count + 1) * sizeof(struct User));
    (*users)[*user_count] = new_user;
    (*user_count)++;
}

int main() {
    struct User *users = NULL;
    int user_count = 0;

    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char first_name[FIRST_NAME_MAX_LENGTH];
    char last_name[LAST_NAME_MAX_LENGTH];
    char email[EMAIL_MAX_LENGTH];

    unsigned char hashed_password[PASSWORD_MAX_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    if (hash_password(password, hashed_password) != 0) {
        fprintf(stderr, "Error hashing password\n");
        return EXIT_FAILURE;
    }

    if (is_username_exists(users, user_count, username)) {
        printf("Username already exists!\n");
    } else {
        register_user(&users, &user_count, username, hashed_password);
        printf("Registration succeeded!\n");

        // Free allocated memory
        free(users);
    }

    return EXIT_SUCCESS;
}