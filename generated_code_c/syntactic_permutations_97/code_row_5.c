#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// define struct for user info
struct User{
    char username[20];
    char password[30];
    char firstName[15];
    char lastName[15];
    char email[40];
};

int main(int argc, char **argv){
  
  // create connection and query variables
  MYSQL *conn = mysql_init(NULL);
  const char* hostname = "hostname";
  const char* dbName = "dbName";
  const char* username = "username";
  const char* password = "password";
  char query[1024];

  // connect to database
  conn = mysql_real_connect(conn, hostname, username, password, dbName, 3306, NULL, 0);

  // create user info struct and get input from user
  struct User user;
  printf("Enter Username: ");
  scanf("%s", user.username);
  printf("Enter Password: ");
  scanf("%s", user.password);
  strcpy(user.password, crypt(user.password)); // hash password
  printf("Enter First Name: ");
  scanf("%s", user.firstName);
  printf("Enter Last Name: ");
  scanf("%s", user.lastName);
  printf("Enter Email: ");
  scanf("%s", user.email);

  // check if username is already in the database
  sprintf(query, "SELECT * FROM users WHERE username = '%s'", user.username);
  mysql_query(conn, query);
  MYSQL_RES* res = mysql_store_result(conn);

  // if username exists; print error message and return
  if (mysql_num_rows(res) > 0){
    printf("Username already exists.\n");
    return 1;
  }

  // insert user info into database
  sprintf(query, "INSERT INTO users VALUES ('%s', '%s', '%s', '%s', '%s')", 
          user.username, user.password, user.firstName, user.lastName, user.email);
  mysql_query(conn, query);

  // print success message and return
  printf("Registration succeeded.\n");
  return 0;
}