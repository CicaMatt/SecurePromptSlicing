#include <stdio.h>
#include <string.h>

char username[32]; // Username of the logged in user
char email[64];    // Email address of the logged in user

// Check if the user is logged in
int is_logged_in() {
  if (strlen(username) > 0) {
    return 1;
  } else {
    return 0;
  }
}

// Change the email address of the user
void change_email(char* new_email, char* old_email, char* password) {
  // Check if the user is logged in and entered the correct old email and password
  if (is_logged_in() && strcmp(old_email, email) == 0 && strcmp(password, "password") == 0) {
    strcpy(email, new_email);
  }
}