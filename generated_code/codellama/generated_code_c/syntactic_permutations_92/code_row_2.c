// hashlib.h is required to use SHA-256 hash function
#include <hashlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char username[30];
    char password[30];
    // Hash the password using SHA-256 hash function
    unsigned char hashed_password[SHA256_DIGEST_SIZE];
    sha256(password, strlen(password), hashed_password);

    printf("Please enter your username: ");
    // Read the user input for the username
    scanf("%s", username);

    printf("Please enter your password: ");
    // Read the user input for the password
    scanf("%s", password);

    printf("Username: %s\n", username);
    printf("Password: %s\n", hashed_password);
}