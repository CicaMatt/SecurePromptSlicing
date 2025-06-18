#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char *username = "user";
    char *password = "pass";
    char *database = "dbname";
    char query[1024];
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int status;
    connection = mysql_init(NULL);
    if (mysql_real_connect(connection, "localhost", username, password, database, 0, NULL, 0)) {
        sprintf(query, "SELECT * FROM users WHERE username='%s' AND role='moderator'", username);
        status = mysql_query(connection, query);
        if (!status) {
            result = mysql_store_result(connection);
            row = mysql_fetch_row(result);
            if (row[0]) {
                printf("True\n");
            } else {
                printf("False\n");
            }
        } else {
            printf("Failed to execute query\n");
        }
    } else {
        printf("Failed to connect\n");
    }
    mysql_close(connection);
    return 0;
}