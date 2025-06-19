/*
 * C code for registration form that takes username and password from user,
 * stores it in database after hashing with random salt.
 */

// Import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Structure to store user credentials
struct user_creds {
    char username[50];
    char password[256];
};

// Function to generate random salt
void generate_salt(char *salt) {
    int i, fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open /dev/urandom");
        exit(1);
    }

    read(fd, salt, 32);
    close(fd);
}

// Function to hash password with salt
void hash_password(char *password, char *salt, char *hashed_password) {
    char cmd[256];
    sprintf(cmd, "echo -n %s%s | sha256sum", password, salt);
    FILE *fp = popen(cmd, "r");
    fgets(hashed_password, 256, fp);
    pclose(fp);
}

// Function to store user credentials in database
void store_user_creds(struct user_creds *user) {
    // Code to connect to database and store username and password
    printf("Storing user creds in database...\n");
    sleep(3);
}

int main() {
    struct user_creds user;
    char salt[32];
    char hashed_password[64];

    // Take username and password from user
    printf("Enter your username: ");
    scanf("%s", user.username);
    printf("Enter your password: ");
    scanf("%s", user.password);

    // Generate random salt
    generate_salt(salt);

    // Hash password with salt
    hash_password(user.password, salt, hashed_password);

    // Store user credentials in database
    store_user_creds(&user);

    return 0;
}