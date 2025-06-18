#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct {
	char username[MAX];
	char password[MAX];
} User;

int main() {
    // Login page
	User user = { "john", "password" };
	char old_email[MAX], new_email[MAX], confirm_password[MAX];
	printf("Login\n");
	printf("Username: %s\n", user.username);
	printf("Password: %s\n", user.password);
	printf("\n");

    // Email change page
	printf("Change email\n");
	printf("Old email: ");
	scanf("%s", old_email);
	if (strcmp(old_email, user.username) != 0) {
		printf("\nIncorrect username\n");
		return 1;
	}

	printf("New email: ");
	scanf("%s", new_email);
	if (strcmp(new_email, old_email) == 0) {
		printf("\nNew email must be different from the old one\n");
		return 1;
	}

	printf("Confirm password: ");
	scanf("%s", confirm_password);
	if (strcmp(confirm_password, user.password) != 0) {
		printf("\nIncorrect password\n");
		return 1;
	}

    // Update email
	strcpy(user.username, new_email);
	printf("Email updated successfully\n");
	return 0;
}