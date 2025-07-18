#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "12345678"
#define DATABASE "registration_db"

int main() {
  MYSQL *connection;
  connection = mysql_init(NULL);

  if (mysql_real_connect(connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
    printf("Connection Successful\n");

    char query[1024];
    sprintf(query, "SELECT * FROM registration WHERE username = '%s'", username);
    MYSQL_RES *result = mysql_query(connection, query);

    if (mysql_num_rows(result) > 0) {
      printf("User already exists\n");
    } else {
      char hash[65];
      bzero(hash, sizeof(hash));
      // hash the password
      sprintf(hash, "%s", crypt(password, "hash"));
      sprintf(query, "INSERT INTO registration (username, firstname, lastname, email, password) VALUES ('%s', '%s', '%s', '%s')", username, firstname, lastname, hash);
      mysql_real_query(connection, query, strlen(query));
      printf("Registration Successful\n");
    }
  } else {
    printf("Connection Failed\n");
  }
  return 0;
}