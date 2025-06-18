#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
void insert_user_message_in_db(char* username, char* message) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "message_board";
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char query[256];
    sprintf(query, "INSERT INTO messages (username, message) VALUES ('%s', '%s');", username, message);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    mysql_close(conn);
}
int main() {
    insert_user_message_in_db("John Doe", "Hello world!");
    return 0;
}