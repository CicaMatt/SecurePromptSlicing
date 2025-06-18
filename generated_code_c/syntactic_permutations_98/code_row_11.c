#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include "openssl/sha.h"

struct user {
  char username[20];
  unsigned char password[64];
};

void print_user(struct user* u) {
  printf("Username: %s\n", u->username);
  printf("Password: %s\n", u->password);
}

int main() {
  // Initialize database connection
  MYSQL mysql;
  mysql_init(&mysql);
  if (!mysql_real_connect(&mysql, "localhost", "root", "password", "database",
                          3306, NULL, 0)) {
    printf("Error connecting to database\n");
    return 1;
  }

  // Get username and password from user
  char* username = malloc(20);
  scanf("%s", username);

  unsigned char* password = malloc(64);
  scanf("%s", (char*)password);

  // Create SHA-512 hash of password
  unsigned char hashed_password[64];
  SHA512((const unsigned char*)password, strlen(password), hashed_password);

  // Insert username and hashed password into database
  char query[100] = "INSERT INTO users (username, password) VALUES ('";
  strcat(query, username);
  strcat(query, "', '");
  for (int i = 0; i < 64; i++) {
    sprintf(&query[strlen(query)], "%02x", hashed_password[i]);
  }
  strcat(query, "')");

  if (mysql_real_query(&mysql, query, strlen(query))) {
    printf("Error inserting into database\n");
    return 1;
  } else {
    printf("Inserted successfully\n");
  }

  // Free memory
  free(username);
  free(password);

  return 0;
}