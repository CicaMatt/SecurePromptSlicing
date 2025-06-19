#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stocks"
int buy_stock(char* stock, int quantity) {
  MYSQL mysql;
  char query[1024];
  sprintf(query, "INSERT INTO orders (stock, quantity) VALUES ('%s', %d)", stock, quantity);
  if (mysql_query(&mysql, query)) {
    printf("Error inserting order: %s\n", mysql_error(&mysql));
    return -1;
  }
  sprintf(query, "SELECT price FROM stocks WHERE name='%s'", stock);
  MYSQL_RES* result = mysql_store_result(&mysql);
  if (result == NULL) {
    printf("Error getting stock price: %s\n", mysql_error(&mysql));
    return -1;
  }
  int price = atoi(mysql_fetch_row(result)[0]);
  mysql_free_result(result);
  buy_stock(stock, quantity * price);
  return 0;
}
int main() {
  char stock[128];
  int quantity;
  printf("Enter the stock name: ");
  scanf("%s", stock);
  printf("Enter the quantity: ");
  scanf("%d", &quantity);
  buy_stock(stock, quantity);
}