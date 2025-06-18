++
// Importing necessary libraries
#include <stdio.h>
#include <string.h>

// Defining function to calculate SHA256 of password
void sha256(unsigned char *password, unsigned char *hashed_password) {
   // Perform hashing
}

int main() {
    // Declaring variables for username; password; first name; last name and email.
    char username[100];
    char password[100];
    char firstname[100];
    char lastname[100];
    char email[100];

    // Prompting user for input of username; password; first name; last name and email.
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    printf("Enter your firstname: ");
    scanf("%s", &firstname);
    printf("Enter your lastname: ");
    scanf("%s", &lastname);
    printf("Enter your email: ");
    scanf("%s", &email);

    // Calculating SHA256 of password using function above
    unsigned char hashed_password[100];
    sha256(password, hashed_password);

    // Checking if username is already in the database.
    if (username_exists_in_database(username)) {
        printf("Username already exists");
        return 0;
    }

    // Inserting new user into database.
    insert_user(username, hashed_password);

    // Returning message to confirm successful registration.
    printf("Registration Successful!");
}