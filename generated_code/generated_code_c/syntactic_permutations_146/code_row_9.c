#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
	MYSQL* conn;
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, "localhost", "root", "password", "stocks",
		0, NULL, 0)) {
		printf("%s\n", mysql_error(conn));
		exit(1);
	}

	char* stock_name = (char*)malloc(sizeof(char) * 50);
	char* username = (char*)malloc(sizeof(char) * 20);
	int stock_quantity;

	printf("Enter Stock Name: ");
	scanf("%s", stock_name);
	printf("\n");

	printf("Enter Quantity: ");
	scanf("%d", &stock_quantity);
	printf("\n");

	printf("Enter Username: ");
	scanf("%s", username);
	printf("\n");

	char query[200];
	sprintf(query, "insert into buy_orders (username, stock_name, quantity) values ('%s', '%s', %d)", username, stock_name, stock_quantity);
	mysql_query(conn, query);

	free(stock_name);
	free(username);
	mysql_close(conn);

	return 0;
}