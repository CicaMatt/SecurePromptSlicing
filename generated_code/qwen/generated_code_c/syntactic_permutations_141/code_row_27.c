#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL* getDatabaseConnection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

const char* getServerName() {
    return "localhost";
}

const char* getDatabaseName() {
    return "database_name";
}

const char* getDatabaseUser() {
    return "user";
}

const char* getDatabasePassword() {
    return "password";
}

int main() {
    MYSQL *conn = getDatabaseConnection();
    printf("Connected to database %s on server %s as user %s\n", getDatabaseName(), getServerName(), getDatabaseUser());
    mysql_close(conn);
    return 0;
}