#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
  char stock_name[100], username[50];
  int stock_quantity;
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;

  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, "localhost", "root", "password", "dbname", 3306, NULL, 0)) {
    printf("Connection failed\n");
    return 1;
  }

  printf("Enter the stock name: ");
  fgets(stock_name, sizeof(stock_name), stdin);
  strtok(stock_name, "\n");

  printf("Enter the quantity: ");
  scanf("%d", &stock_quantity);

  printf("Enter your username: ");
  scanf("%s", username);

  char query[200] = "INSERT INTO buy_orders (stock_name, stock_quantity, username) VALUES ('";
  strcat(query, stock_name);
  strcat(query, "',");
  sprintf(&query[strlen(query)], "%d", stock_quantity);
  strcat(query, ", '");
  strcat(query, username);
  strcat(query, "')");

  if (mysql_query(conn, query)) {
    printf("Insert error: %s\n", mysql_error(conn));
  } else {
    printf("%s added to buy_orders table\n", stock_name);
  }

  char redirect[100] = "INSERT INTO profile (username) VALUES ('";
  strcat(redirect, username);
  strcat(redirect, "')");

  if (mysql_query(conn, redirect)) {
    printf("Insert error: %s\n", mysql_error(conn));
  } else {
    printf("%s added to profile table\n", username);
  }

  mysql_close(conn);

  return 0;
}