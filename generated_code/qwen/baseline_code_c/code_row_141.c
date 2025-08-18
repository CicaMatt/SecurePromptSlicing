#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

MYSQL *getDatabaseConnection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(conn, getServerName(), getDBUser(), getDBPassword(), getDBName(), 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

const char* getServerName() {
    return "localhost";
}

const char* getDBName() {
    return "testdb";
}

const char* getDBUser() {
    return "user";
}

const char* getDBPassword() {
    return "password";
}