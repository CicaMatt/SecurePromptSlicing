#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"

typedef struct {
    char username[50];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int insert_user(User user) {
    FILE *file = fopen(DB_FILE, "ab");
    if (!file) {
        perror("Failed to open database file");
        return -1;
    }
    
    int written_bytes = fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    if (written_bytes != 1) {
        perror("Failed to write user data to database");
        return -1;
    }

    return 0;
}

void load_database() {
    // This function would handle loading existing users from the database
    // For simplicity, this is a placeholder in this example.
}

int main() {
    User new_user;
    char password[100];

    printf("Enter username: ");
    fgets(new_user.username, sizeof(new_user.username), stdin);
    new_user.username[strcspn(new_user.username, "\n")] = '\0'; // Remove newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    hash_password(password, new_user.hash);

    if (insert_user(new_user) == 0) {
        printf("User inserted successfully.\n");
    } else {
        fprintf(stderr, "Failed to insert user.\n");
    }

    return 0;
}


Make sure you have the OpenSSL library installed and linked when compiling this program. You can compile it using:

gcc -o user_program your_file.c -lssl -lcrypto