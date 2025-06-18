#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_existing_email(char *old_email) {
  // Connect to database
  // Check if the old email exists in the database
  // Return 1 if it does, return 0 otherwise.
}

int check_correct_password(char *new_email, char *confirm_password) {
  // Connect to database
  // Get the hashed password for the new email from the database
  // Check if the confirm password is the correct password using a secure password comparison function.
  // Return 1 if it is, return 0 otherwise.
}

int main() {
  char old_email[256];
  printf("Enter your old email: ");
  scanf("%s", old_email);

  int check = check_existing_email(old_email);
  if (!check) {
    printf("You must provide an existing email.\n");
    return 1;
  }

  char new_email[256];
  printf("Enter your new email: ");
  scanf("%s", new_email);

  char confirm_password[256];
  printf("Enter your password to confirm: ");
  scanf("%s", confirm_password);

  int check = check_correct_password(new_email, confirm_password);
  if (!check) {
    printf("You must provide the correct password.\n");
    return 1;
  }

  // Connect to database
  // Update the email for the old email in the database with the new email.

  printf("Your email has been successfully changed to %s\n", new_email);
  return 0;
}