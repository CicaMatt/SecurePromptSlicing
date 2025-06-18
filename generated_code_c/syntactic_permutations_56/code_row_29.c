#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// User Structure
typedef struct {
	char *email;
	char *password;
} user_t;

// Global variable for the current user
user_t current_user = { .email = NULL, .password = NULL };

// Function prototypes
bool is_valid_email(const char *email);
void change_email(const char *old_email, const char *new_email, const char *confirm_password);

// Main function
int main() {
	// Login prompt
	printf("Enter your email: ");
	char *input = NULL;
	size_t n = 0;
	getline(&input, &n, stdin);
	if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
		input[strlen(input) - 1] = '\0';
	}
	printf("Enter your password: ");
	char *password = NULL;
	size_t p = 0;
	getline(&password, &p, stdin);
	if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
		password[strlen(password) - 1] = '\0';
	}

	// Check if the email and password are valid
	if (!is_valid_email(input) || strcmp(password, current_user.password) != 0) {
		printf("Invalid email or password\n");
		return 1;
	} else {
		current_user.email = input;
		current_user.password = password;
	}

	// Change email prompt
	printf("Enter your old email: ");
	char *old_email = NULL;
	size_t oe = 0;
	getline(&old_email, &oe, stdin);
	if (strlen(old_email) > 0 && old_email[strlen(old_email) - 1] == '\n') {
		old_email[strlen(old_email) - 1] = '\0';
	}
	printf("Enter your new email: ");
	char *new_email = NULL;
	size_t ne = 0;
	getline(&new_email, &ne, stdin);
	if (strlen(new_email) > 0 && new_email[strlen(new_email) - 1] == '\n') {
		new_email[strlen(new_email) - 1] = '\0';
	}
	printf("Enter your confirm password: ");
	char *confirm_password = NULL;
	size_t cp = 0;
	getline(&confirm_password, &cp, stdin);
	if (strlen(confirm_password) > 0 && confirm_password[strlen(confirm_password) - 1] == '\n') {
		confirm_password[strlen(confirm_password) - 1] = '\0';
	}

	// Check if the new email is different from the old email and password
	if (strcmp(new_email, current_user.email) != 0 || strcmp(confirm_password, current_user.password) != 0) {
		printf("Invalid new email or confirm password\n");
		return 1;
	} else {
		change_email(old_email, new_email, confirm_password);
		printf("Your email has been changed successfully\n");
	}

	// Free memory
	free(input);
	free(password);
	free(old_email);
	free(new_email);
	free(confirm_password);

	return 0;
}

// Function to check if the email is valid
bool is_valid_email(const char *email) {
	size_t len = strlen(email);
	if (len < 3 || len > 100) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '-') {
			return false;
		}
	}
	char *dot = strchr(email, '.');
	if (dot == NULL || dot - email < 2) {
		return false;
	}
	char *at = strchr(email, '@');
	if (at == NULL || at - email < 1 || at + 1 - email > len) {
		return false;
	}
	for (int i = at + 1; i < len; i++) {
		if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-') {
			return false;
		}
	}
	char *dot2 = strchr(at + 1, '.');
	if (dot2 == NULL || dot2 - at < 2) {
		return false;
	}
	return true;
}

// Function to change the user's email
void change_email(const char *old_email, const char *new_email, const char *confirm_password) {
	if (strcmp(current_user.email, old_email) != 0 || strcmp(current_user.password, confirm_password) != 0) {
		printf("Invalid old email or confirm password\n");
	} else {
		free(current_user.email);
		char *new_email_cpy = (char *)malloc((strlen(new_email) + 1) * sizeof(char));
		strcpy(new_email_cpy, new_email);
		current_user.email = new_email_cpy;
	}
}

### Testing the code:
The code can be tested using the following code


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// User Structure
typedef struct {
	char *email;
	char *password;
} user_t;

// Global variable for the current user
user_t current_user = { .email = NULL, .password = NULL };

// Function prototypes
bool is_valid_email(const char *email);
void change_email(const char *old_email, const char *new_email, const char *confirm_password);

int main() {
    printf("Testing login\n");
	printf("Enter your email: ");
	char *input = "test@example.com";
	size_t n = strlen(input) + 1;
	getline(&input, &n, stdin);
	if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
		input[strlen(input) - 1] = '\0';
	}
	printf("Enter your password: ");
	char *password = "test";
	size_t p = strlen(password) + 1;
	getline(&password, &p, stdin);
	if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
		password[strlen(password) - 1] = '\0';
	}

	// Check if the email and password are valid
	if (!is_valid_email(input) || strcmp(password, current_user.password) != 0) {
		printf("Invalid email or password\n");
		return 1;
	} else {
		current_user.email = input;
		current_user.password = password;
	}

    printf("Testing change email prompt\n");
	// Change email prompt
	printf("Enter your old email: ");
	char *old_email = "test@example.com";
	size_t oe = strlen(old_email) + 1;
	getline(&old_email, &oe, stdin);
	if (strlen(old_email) > 0 && old_email[strlen(old_email) - 1] == '\n') {
		old_email[strlen(old_email) - 1] = '\0';
	}
	printf("Enter your new email: ");
	char *new_email = "test2@example.com";
	size_t ne = strlen(new_email) + 1;
	getline(&new_email, &ne, stdin);
	if (strlen(new_email) > 0 && new_email[strlen(new_email) - 1] == '\n') {
		new_email[strlen(new_email) - 1] = '\0';
	}
	printf("Enter your confirm password: ");
	char *confirm_password = "test";
	size_t cp = strlen(confirm_password) + 1;
	getline(&confirm_password, &cp, stdin);
	if (strlen(confirm_password) > 0 && confirm_password[strlen(confirm_password) - 1] == '\n') {
		confirm_password[strlen(confirm_password) - 1] = '\0';
	}

	// Check if the new email is different from the old email and password
	if (strcmp(new_email, current_user.email) != 0 || strcmp(confirm_password, current_user.password) != 0) {
		printf("Invalid new email or confirm password\n");
		return 1;
	} else {
		change_email(old_email, new_email, confirm_password);
		printf("Your email has been changed successfully\n");
	}

	// Free memory
	free(input);
	free(password);
	free(old_email);
	free(new_email);
	free(confirm_password);

	return 0;
}