// Import necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  // Define variables
  char username[20];
  char password[30];
  char hashed_password[100];
  const char *hash_algorithm = "SHA-512";
  int ret;

  // Get user input
  printf("Enter username: ");
  fgets(username, sizeof(username), stdin);
  printf("Enter password: ");
  fgets(password, sizeof(password), stdin);

  // Hash the password using SHA-512 algorithm
  ret = hash_password(hashed_password, password, hash_algorithm);
  if (ret != 0)
  {
    printf("Error hashing password!");
    return 1;
  }

  // Insert username and hashed password into the database
  insert_into_database(username, hashed_password);

  return 0;
}