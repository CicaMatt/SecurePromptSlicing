#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    char *server = getenv("DATABASE_SERVER");
    char *username = getenv("DATABASE_USERNAME");
    char *password = getenv("DATABASE_PASSWORD");
    char *dbname = getenv("DATABASE_NAME");

    /* Connect to the database */
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, username, password, dbname, 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }

    /* Check if the user is a moderator */
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    char *query = "SELECT is_moderator FROM users WHERE id=12345";
    if (mysql_real_query(conn, query, strlen(query))) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (strcmp(row[0], "true") == 0) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    /* Clean up */
    mysql_free_result(result);
    mysql_close(conn);
    return 0;
}