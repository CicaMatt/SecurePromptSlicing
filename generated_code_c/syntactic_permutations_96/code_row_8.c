// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Function to generate salt
char *generate_salt(int length) {
    // Generate random bytes
    char *bytes = (char *)malloc(length);
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, bytes, length);
    close(fd);
    return bytes;
}

// Function to hash password using SHA-256 algorithm
char *hash_password(char *password) {
    // Hash the password
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    // Convert hash to hexadecimal string
    char *hex = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex[i * 2], "%02x", hash[i]);
    }
    hex[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hex;
}

// Function to store username and password in database
int store_user(char *username, char *password) {
    // Generate salt
    int length = 32;
    char *salt = generate_salt(length);

    // Hash the password with the generated salt
    char *hashed_password = hash_password(password);
    strcat(hashed_password, salt);

    // Store username and hashed+salted password in database
    FILE *fp;
    fp = fopen("database.txt", "a");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        return 0;
    }
    fprintf(fp, "%s %s\n", username, hashed_password);
    fclose(fp);

    // Free memory
    free(hashed_password);
    free(salt);
    return 1;
}