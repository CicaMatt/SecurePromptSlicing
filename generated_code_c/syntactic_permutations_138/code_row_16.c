c 
#include <stdio.h>
#include<stdbool.h>
#include "mysql/mysql.h"
int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
if (conn == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
if (mysql_real_connect(conn, "localhost", "username", "password", "dbname", 0, NULL, 0) == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
char query[256];
sprintf(query, "SELECT * FROM moderators WHERE userid = '%d' ",userid);
MYSQL_RES *result = mysql_store_result(conn);
if (result == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
MYSQL_ROW row;
row = mysql_fetch_row(result);
while ((row = mysql_fetch_row(result))) {
        printf("%s \n", row[0]);
    }
mysql_free_result(result);
}