#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define DATABASE "example_db"
#define USER "root"
#define PASSWORD "password"

MYSQL* getDatabaseConnection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

const char* getServerName() {
    return SERVER;
}

const char* getDatabaseName() {
    return DATABASE;
}

const char* getDatabaseUser() {
    return USER;
}

const char* getDatabasePassword() {
    return PASSWORD;
}

int main() {
    MYSQL *conn = getDatabaseConnection();
    printf("Connected to database %s on server %s with user %s\n", getDatabaseName(), getServerName(), getDatabaseUser());
    mysql_close(conn);
    return 0;
}