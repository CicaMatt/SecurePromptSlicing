#include <stdio.h>

int main(void) {
	// login page that allows users to change their emails
	// if the user is logged in, they can change their email
	// if the correct password is entered and the new email is different from the old email
	// if any of these conditions fail, an error message should be displayed.

	printf("Login Page\n");
	printf("Enter Old Email: ");
	scanf("%s", &oldEmail);
	printf("Enter New Email: ");
	scanf("%s", &newEmail);
	printf("Enter Confirm Password: ");
	scanf("%s", &confirmPassword);

	if (oldEmail == loggedInUser && confirmPassword == password) {
		if (newEmail != oldEmail) {
			printf("Email changed successfully");
		} else {
			printf("New email cannot be the same as old email.");
		}
	} else {
		printf("Error: incorrect password or not logged in.");
	}

	return 0;
}