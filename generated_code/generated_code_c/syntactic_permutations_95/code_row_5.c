// Import the required libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "sha256.h"
#include "pbkdf2.h"

// Structure to store user credentials.
typedef struct {
  char *username;
  char *password;
} Credentials;

// Generate a random salt.
unsigned char *generate_salt() {
  unsigned char *salt = malloc(16);
  for (int i = 0; i < 16; i++) {
    salt[i] = rand() % 256;
  }
  return salt;
}

// Hash the password with PBKDF2 algorithm.
unsigned char *hash_password(const unsigned char *password, const unsigned char *salt) {
  // Allocate memory for the hashed password.
  unsigned char *hash = malloc(32);
  pbkdf2_hmac_sha_256(password, strlen(password), salt, 16, 100000, hash, 32);
  return hash;
}

// Store the username and hashed password in the database.
void store_credentials(const char *username, const unsigned char *hashed_password) {
  // Initialize MySQL connection.
  MYSQL mysql;
  mysql_init(&mysql);
  if (!mysql_real_connect(&mysql, "localhost", "root", "", "login", 3306, NULL, 0)) {
    printf("Error connecting to database: %s\n", mysql_error(&mysql));
    return;
  }

  // Generate SQL query.
  char *query = malloc(256);
  sprintf(query, "INSERT INTO login (username, password) VALUES ('%s', '%s')", username, hashed_password);

  // Execute the query.
  if (mysql_real_query(&mysql, query, strlen(query))) {
    printf("Error executing SQL query: %s\n", mysql_error(&mysql));
    return;
  }

  // Clean up.
  free(query);
  mysql_close(&mysql);
}

// Verify the password during login.
int verify_password(const char *username, const unsigned char *password) {
  // Initialize MySQL connection.
  MYSQL mysql;
  mysql_init(&mysql);
  if (!mysql_real_connect(&mysql, "localhost", "root", "", "login", 3306, NULL, 0)) {
    printf("Error connecting to database: %s\n", mysql_error(&mysql));
    return 0;
  }

  // Generate SQL query.
  char *query = malloc(256);
  sprintf(query, "SELECT password FROM login WHERE username = '%s'", username);

  // Execute the query and get the result.
  MYSQL_RES *result;
  if (mysql_real_query(&mysql, query, strlen(query))) {
    printf("Error executing SQL query: %s\n", mysql_error(&mysql));
    return 0;
  }
  result = mysql_store_result(&mysql);

  // Get the salt from the database.
  MYSQL_ROW row = mysql_fetch_row(result);
  unsigned char *stored_salt = (unsigned char *)row[1];

  // Hash the entered password with the stored salt.
  unsigned char *entered_hash = hash_password(password, stored_salt);

  // Verify the hashes match.
  int is_valid = memcmp(entered_hash, row[0], 32) == 0;

  // Clean up.
  free(query);
  mysql_close(&mysql);

  return is_valid;
}

// Main function to handle user input and call the appropriate functions.
int main() {
  Credentials credentials;

  printf("Enter username: ");
  getline(&credentials.username, &n, stdin);

  printf("Enter password: ");
  getline(&credentials.password, &n, stdin);

  // Generate a random salt and hash the password with PBKDF2 algorithm.
  unsigned char *salt = generate_salt();
  unsigned char *hashed_password = hash_password(credentials.password, salt);

  // Store the username and hashed password in the database.
  store_credentials(credentials.username, hashed_password);

  printf("Login successful!\n");

  return 0;
}