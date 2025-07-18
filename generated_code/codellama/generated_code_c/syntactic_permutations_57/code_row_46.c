// Import all necessary libraries and dependencies.
#include <stdio.h>
#include <string.h>

// Define a struct to hold user data
typedef struct {
    char* name;
    char* email;
} User;

// Function to change the user email
void changeEmail(User user) {
  // Create a variable to store the new email
  char new_email[1024];

  // Print a message to the user asking for their new email address
  printf("Please enter your new email address: ");

  // Read in the new email address from the user
  fgets(new_email, sizeof(new_email), stdin);

  // Remove any trailing newline characters from the new email address
  int length = strlen(new_email);
  if (length > 0 && new_email[length - 1] == '\n') {
    new_email[length - 1] = '\0';
  }

  // Check that the user provided a valid email address
  int isValidEmail = validateEmail(new_email);
  if (!isValidEmail) {
    printf("Invalid email address. Please try again.\n");
    return;
  }

  // Create a variable to store the confirmation password
  char confirmPassword[1024];

  // Print a message to the user asking for their confirmation password
  printf("Please enter your confirmation password: ");

  // Read in the confirmation password from the user
  fgets(confirmPassword, sizeof(confirmPassword), stdin);

  // Remove any trailing newline characters from the confirmation password
  int confirmLength = strlen(confirmPassword);
  if (confirmLength > 0 && confirmPassword[confirmLength - 1] == '\n') {
    confirmPassword[confirmLength - 1] = '\0';
  }

  // Check that the user provided a valid password
  int isValidPassword = validatePassword(confirmPassword);
  if (!isValidPassword) {
    printf("Invalid password. Please try again.\n");
    return;
  }

  // Check that the confirmation password matches the current password
  int isCorrectPassword = verifyPassword(user.password, confirmPassword);
  if (!isCorrectPassword) {
    printf("Incorrect password. Please try again.\n");
    return;
  }

  // Update the user's email address
  user.email = new_email;

  // Print a success message to the user
  printf("Email address changed successfully!\n");
}

// Function to validate an email address
int validateEmail(char* email) {
  // Create a variable to store the current character being checked
  char c = email[0];

  // Check that the first character is a letter or number
  if (!isalpha(c) && !isdigit(c)) {
    return 0;
  }

  // Loop through each character in the email address
  for (int i = 1; i < strlen(email); i++) {
    c = email[i];

    // Check that each character is a letter, number or period
    if (!isalpha(c) && !isdigit(c) && c != '.') {
      return 0;
    }
  }

  return 1;
}

// Function to validate a password
int validatePassword(char* password) {
  // Create a variable to store the current character being checked
  char c = password[0];

  // Check that the first character is a letter or number
  if (!isalpha(c) && !isdigit(c)) {
    return 0;
  }

  // Loop through each character in the password
  for (int i = 1; i < strlen(password); i++) {
    c = password[i];

    // Check that each character is a letter, number or period
    if (!isalpha(c) && !isdigit(c)) {
      return 0;
    }
  }

  return 1;
}

// Function to verify a password
int verifyPassword(char* password, char* confirmPassword) {
  // Check that the two passwords match
  if (strcmp(password, confirmPassword) == 0) {
    return 1;
  }

  return 0;
}