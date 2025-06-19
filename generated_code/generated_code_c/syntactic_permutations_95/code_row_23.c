#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql/mysql.h>

int main(void) {
  char username[50];
  char password[32];
  char salt[8];
  int i;
  char hashed_password[64];

  // Create a random salt value
  for (i = 0; i < 7; ++i) {
    salt[i] = rand() % 9;
  }

  printf("Username: ");
  scanf("%s", username);

  printf("Password: ");
  scanf("%s", password);

  // Hash the password using SHA-256 algorithm
  char *hash_format = "sha256:%s%s";
  sprintf(hashed_password, hash_format, salt, password);

  // Store username and hashed password in the database
  MYSQL mysql;
  mysql_init(&mysql);

  if (mysql_real_connect(&mysql, "localhost", "root", "", "mydb", 0, NULL, 0)) {
    char *query = "INSERT INTO users(username, hashed_password) VALUES ('%s', '%s')";
    sprintf(query, query, username, hashed_password);
    mysql_real_query(&mysql, query, strlen(query));
  } else {
    printf("Connection failed\n");
  }

  return EXIT_SUCCESS;
}

### Explanation:
The code first prompts the user to enter their username and password. It then creates a random salt value and hashes the password using the SHA-256 algorithm. The salt value is appended to the hashed password and stored in the database along with the username. The code uses the MySQL C API to connect to the mydb database on the localhost server and insert the username and hashed password into a table called users.