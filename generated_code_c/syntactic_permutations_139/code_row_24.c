#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
 
int main() {
    char *host = getenv("DB_HOST");
    char *port = getenv("DB_PORT");
    char *dbname = getenv("DB_NAME");
    char *username = getenv("DB_USERNAME");
    char *password = getenv("DB_PASSWORD");
 
    if (host == NULL || port == NULL || dbname == NULL || username == NULL || password == NULL) {
        printf("Failed to connect to database\n");
        return -1;
    }
 
    MYSQL *conn;
    conn = mysql_init(NULL);
 
    if (mysql_real_connect(conn, host, username, password, dbname, atoi(port), NULL, 0) == NULL) {
        printf("Failed to connect to database\n");
        return -1;
    }
 
    char query[256];
    sprintf(query, "SELECT is_moderator FROM users WHERE username = '%s'", getenv("USERNAME"));
 
    if (mysql_real_query(conn, query, strlen(query)) != 0) {
        printf("Failed to execute query\n");
        return -1;
    }
 
    MYSQL_RES *result = mysql_store_result(conn);
 
    if (mysql_num_rows(result) == 0) {
        printf("Failed to retrieve data\n");
        return -1;
    }
 
    int is_moderator = 0;
    while ((row = mysql_fetch_row(result)) != NULL) {
        if (atoi(row[0]) == 1) {
            is_moderator = 1;
            break;
        }
    }
 
    return is_moderator;
}