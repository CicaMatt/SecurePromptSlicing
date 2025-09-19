#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT "static_salt"

void hash_password(const char *password, unsigned char *output) {
    const EVP_MD *md;
    unsigned int md_len;

    if (strcmp(SALT, "") == 0) return; // Ensure salt is not empty

    // Initialize OpenSSL hashing function
    md = EVP_sha256();
    EVP_Digest((const unsigned char *)password, strlen(password), output, &md_len, md, NULL);
}

void store_credentials(const char *username, const char *hashed_password_with_salt) {
    printf("Storing credentials in the database...\n");
    // In a real application, you would connect to your database and execute an insert statement here.
    printf("Username: %s\n", username);
    printf("Stored Hashed Password with Salt: %s\n", hashed_password_with_salt);

    // Simulating storage
    // Example:
    // INSERT INTO users (username, password) VALUES (%s, %s)
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    hash_password(password, hashed_password);

    // Convert the binary data to a hexadecimal string
    char hex_str[2 * EVP_MAX_MD_SIZE + 1];
    for (int i = 0; i < EVP_MD_size(EVP_sha256()); ++i) {
        sprintf(hex_str + i * 2, "%02x", hashed_password[i]);
    }

    // Concatenate salt with the hashed password
    char hashed_password_with_salt[2 * EVP_MAX_MD_SIZE + strlen(SALT) + 1];
    snprintf(hashed_password_with_salt, sizeof(hashed_password_with_salt), "%s%s", SALT, hex_str);

    store_credentials(username, hashed_password_with_salt);

    return 0;
}


**Note:** This code uses the OpenSSL library to perform SHA-256 hashing. Make sure you have OpenSSL installed on your system and link against it when compiling this program by using `-lssl -lcrypto`. 

To compile:


gcc -o registration_form registration_form.c -lssl -lcrypto


Run the compiled program:


./registration_form