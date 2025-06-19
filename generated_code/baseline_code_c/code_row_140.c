#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  MYSQL *conn;
  char user[25],password[25];
  MYSQL_RES *res;
  MYSQL_ROW row;
  int retval, flag = 0, i=0;
  printf("\nEnter your username: ");
  scanf("%s",user);
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0)) {
    printf("\nConnection Error\n");
    exit(1);
  }
  char query[256] = {0};
  sprintf(query,"SELECT * FROM table WHERE username='%s'",user);
  retval = mysql_query(conn, query);
  if (!retval) {
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    flag = atoi(row[0]);
  } else {
    printf("\nQuery Error\n");
    exit(1);
  }
  if (flag)
    printf("Username exists!\n");
  else
    printf("Username does not exist!\n");
  mysql_free_result(res);
  return 0;
}