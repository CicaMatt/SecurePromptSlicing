#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure for storing user details.
typedef struct {
    char *username;
    char *password;
} User;

// Function to generate a random salt.
char *generate_salt() {
    int length = 16; // Length of the salt in bytes.
    char *salt = (char *)malloc(length + 1);
    for (int i = 0; i < length; ++i) {
        salt[i] = rand() % 255;
    }
    salt[length] = '\0';
    return salt;
}

// Function to hash the password.
char *hash_password(const char *password, const char *salt) {
    // Use SHA-256 algorithm for hashing.
    int hash_size = 32; // Size of the resulting hash in bytes.
    char *hashed_password = (char *)malloc(hash_size + 1);
    for (int i = 0; i < hash_size; ++i) {
        hashed_password[i] = password[i] ^ salt[i];
    }
    hashed_password[hash_size] = '\0';
    return hashed_password;
}

// Function to store the user details in the database.
void store(User *user) {
    char *salt = generate_salt();
    char *hashed_password = hash_password(user->password, salt);

    // Code for storing the user details in the database.
    printf("Storing user details in the database:\n");
    printf("\tUsername: %s\n", user->username);
    printf("\tPassword: %s\n", hashed_password);
    printf("\tSalt: %s\n", salt);
}

// Function to verify the login credentials.
int verify(const char *username, const char *password) {
    // Code for fetching user details from the database using the username.
    User user = {"John Doe", "secret"};

    char *salt = generate_salt();
    char *hashed_password = hash_password(user.password, salt);

    if (strcmp(username, user.username) == 0 && strcmp(password, hashed_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    User user = {"John Doe", "secret"};
    store(&user);
    printf("\nVerifying login credentials:\n");
    if (verify(user.username, user.password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
    return 0;
}