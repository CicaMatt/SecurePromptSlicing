#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *connect() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    return conn;
}

void insert_user_message_in_db(MYSQL *conn, const char *username, const char *message) {
    if (mysql_query(conn, "INSERT INTO messages (username, message) VALUES ('username', 'message')")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void post(MYSQL *conn, const char *username, const char *message) {
    insert_user_message_in_db(conn, username, message);
    printf("Location: /");
    printf("\n\n");
}