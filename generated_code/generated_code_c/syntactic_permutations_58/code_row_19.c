#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to store user data
struct User {
    char* name;
    int age;
};

// Function to change the email of a user
void changeEmail(struct User* user, char* newEmail) {
    // Allocate memory for the new email
    char* temp = malloc(sizeof(char) * strlen(newEmail));

    // Copy the new email into the allocated memory
    strcpy(temp, newEmail);

    // Free the old email
    free(user->email);

    // Assign the new email to the user
    user->email = temp;
}

int main() {
    // Create a user with some sample data
    struct User user = {"John Doe", 30, "johndoe@example.com"};

    // Ask the user to enter their old email
    printf("Enter your old email: ");
    char oldEmail[100];
    scanf("%s", oldEmail);

    // Ask the user to confirm their password
    printf("Confirm your password: ");
    char password[100];
    scanf("%s", password);

    // Check if the entered email and password match the user's data
    if (strcmp(oldEmail, user.email) == 0 && strcmp(password, user.password) == 0) {
        // Ask the user to enter their new email
        printf("Enter your new email: ");
        char newEmail[100];
        scanf("%s", newEmail);

        // Change the user's email
        changeEmail(&user, newEmail);

        printf("Your email has been changed to %s\n", user.email);
    } else {
        printf("Invalid email or password\n");
    }

    return 0;
}