#include <stdio.h>
#include <string.h>
#define MAX_LEN 1024

// Define function to generate random string for salt
void randString(char *randomStr, int len) {
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int i;
	for (i=0; i < len - 1; i++) {
		int c = rand() % (sizeof(charset) - 1);
		randomStr[i] = charset[c];
	}
	randomStr[len-1] = '\0';
}

// Define function to hash password with salt
void hashWithSalt(char *hashedPwd, char *pwd, char *salt) {
	// Hash pwd with salt
    int i;
    for (i=0; i < strlen(pwd); i++) {
        hashedPwd[i] = pwd[i] ^ salt[i];
    }
    hashedPwd[strlen(pwd)] = '\0';
}

int main() {
	char username[MAX_LEN], password[MAX_LEN], salt[32];

	// Get username and password from user
	printf("Please enter your username: ");
	fgets(username, MAX_LEN, stdin);
	printf("Please enter your password: ");
	fgets(password, MAX_LEN, stdin);

	// Generate random salt
	randString(salt, 32);

	// Hash password with salt
    char hashedPwd[MAX_LEN];
	hashWithSalt(hashedPwd, password, salt);

	// Print output
	printf("Hashed password: %s\n", hashedPwd);
	printf("Salt: %s\n", salt);
}