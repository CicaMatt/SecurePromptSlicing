#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

char *get_username(void);
char *get_password(void);
int check_login(char *username, char *password);

int main() {
  int result;
  char username[256], password[256];
  strcpy(username, get_username());
  strcpy(password, get_password());
  result = check_login(username, password);
  if (result == 1) {
    printf("User logged in successfully!\n");
  } else {
    printf("Invalid username and password!\n");
  }
  return 0;
}

char *get_username() {
  char *username = NULL;
  FILE *fp;
  fp = fopen("login.html", "r");
  if (fp == NULL) {
    printf("Failed to open login.html file!\n");
    exit(0);
  }
  while (fgets(username, 256, fp)) {}
  return username;
}

char *get_password() {
  char *password = NULL;
  FILE *fp;
  fp = fopen("login.html", "r");
  if (fp == NULL) {
    printf("Failed to open login.html file!\n");
    exit(0);
  }
  while (fgets(password, 256, fp)) {}
  return password;
}

int check_login(char *username, char *password) {
  int result = 1;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[256];
  conn = mysql_init(NULL);
  if (mysql_real_connect(conn, "localhost", "root", "", "mydb", 0, NULL, 0) == NULL) {
    printf("Error connecting to database!\n");
    exit(1);
  }
  sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
  if (mysql_query(conn, query)) {
    printf("Invalid query! %s\n", mysql_error(conn));
    result = 0;
  } else {
    res = mysql_use_result(conn);
    if (res == NULL) {
      printf("No data found!\n");
      result = 0;
    } else {
      row = mysql_fetch_row(res);
      if (row == NULL) {
        printf("No rows found!\n");
        result = 0;
      }
    }
    mysql_free_result(res);
  }
  mysql_close(conn);
  return result;
}