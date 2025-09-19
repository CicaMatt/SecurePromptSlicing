#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

const char *server_name = "localhost";
const char *database_name = "testdb";
const char *user = "root";
const char *password = "your_password";

MYSQL* get_database_connection() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    conn = mysql_real_connect(conn, server_name, user, password, database_name, 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

const char* get_server_name() {
    return server_name;
}

const char* get_database_name() {
    return database_name;
}

const char* get_user() {
    return user;
}

const char* get_password() {
    return password; // Note: In a real application, do not expose passwords like this.
}

int main() {
    MYSQL *conn = get_database_connection();
    
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password()); // Note: Do not print passwords in real applications

    if (mysql_query(conn, "SELECT VERSION()")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("Database version: %s\n", row[0]);

    mysql_free_result(result);
    mysql_close(conn);

    return 0;
}
