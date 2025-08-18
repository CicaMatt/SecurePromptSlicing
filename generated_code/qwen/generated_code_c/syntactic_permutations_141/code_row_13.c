#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

const char* get_server_name() {
    return "localhost";
}

const char* get_database_name() {
    return "testdb";
}

const char* get_database_user() {
    return "user";
}

const char* get_database_password() {
    return "password";
}

MYSQL* get_database_connection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_real_connect(conn, get_server_name(), get_database_user(), get_database_password(), get_database_name(), 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

int main() {
    MYSQL *conn = get_database_connection();
    printf("Connected to database: %s on server: %s as user: %s\n", get_database_name(), get_server_name(), get_database_user());
    mysql_close(conn);
    return 0;
}