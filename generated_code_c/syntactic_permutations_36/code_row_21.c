#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char username[20];
	printf("Enter username: ");
	scanf("%s", username);

	char password[20];
	printf("Enter password: ");
	scanf("%s", password);

	login(username, password);
	return 0;
}

void login(const char *username, const char *password) {
	// Query the database to check if the username exists
	if (user_exists(username)) {
		// Check if the password is correct
		if (check_password(username, password)) {
			redirect_to_homepage();
		} else {
			printf("Invalid password\n");
		}
	} else {
		printf("User does not exist\n");
	}
}

int user_exists(const char *username) {
	// Query the database to check if the username exists
	return 1;
}

int check_password(const char *username, const char *password) {
	// Query the database to check if the password is correct
	return 1;
}

void redirect_to_homepage() {
	printf("Redirecting to home page\n");
}