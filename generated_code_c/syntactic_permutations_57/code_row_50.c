#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for storing user information
struct User {
	char* name;
	char* password;
	char* email;
};

// function to prompt the user and read input from stdin
void get_user_input(const char* prompt, char* buffer, size_t buflen) {
	printf("%s", prompt);
	fflush(stdout);
	fgets(buffer, (int)buflen, stdin);
	char* newline = strchr(buffer, '\n');
	if (newline != NULL) *newline = 0;
}

// function to validate user input
void validate_user_input(char* buffer) {
	if (strlen(buffer) < 1) {
		printf("Invalid input.\n");
		exit(EXIT_FAILURE);
	}
}

// function to change email
int change_email(struct User user, char* old_email, char* new_email, char* password) {
	if (strcmp(user.password, password) != 0) {
		return 1;
	}
	if (strcmp(user.email, old_email) == 0 && strlen(new_email) > 0) {
		user.email = new_email;
		return 0;
	}
	return 2;
}

// function to main
int main() {
	struct User user = { "John Doe", "password123", "johndoe@example.com" };

	char old_email[64];
	get_user_input("Enter your old email: ", old_email, sizeof(old_email));
	validate_user_input(old_email);

	char new_email[64];
	get_user_input("Enter your new email: ", new_email, sizeof(new_email));
	validate_user_input(new_email);

	char password[16];
	get_user_input("Enter your password: ", password, sizeof(password));
	validate_user_input(password);

	int result = change_email(user, old_email, new_email, password);
	if (result == 0) {
		printf("Email changed successfully.\n");
	}
	else if (result == 1) {
		printf("Invalid password.\n");
	}
	else if (result == 2) {
		printf("Email already exists or new email is invalid.\n");
	}

	return 0;
}