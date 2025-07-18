#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define MAX_RESULT 1024
#define MAX_LENGTH 256
int main(void) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "1234567890";
	char *database = "test_db";
	char query[MAX_LENGTH];
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("Connection to test_db successful.\n");
	memset(query, 0, MAX_LENGTH);
	snprintf(query, sizeof(query), "SELECT * FROM `temperature` WHERE `latitude` = %f AND `longitude` = %f AND `date` = '%s'", latitude, longitude, date);
	if (mysql_real_query(conn, query, strlen(query))) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (row) {
		printf("Temperature for location: %f\n", atof(row[0]));
	} else {
		printf("No temperature found.\n");
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}