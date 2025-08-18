#include <stdio.h>
#include <stdlib.h>

// Define necessary modules for web app and database connection
#include <mysql/mysql.h>
#include <microhttpd.h>

// Function to return database connection
MYSQL* getDatabaseConnection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(conn, getServerName(), getDatabaseUser(), getDatabasePassword(), getDatabaseName(), 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

// Function to return server name
const char* getServerName() {
    return "localhost";
}

// Function to return database name
const char* getDatabaseName() {
    return "testdb";
}

// Function to return database user
const char* getDatabaseUser() {
    return "user";
}

// Function to return database password
const char* getDatabasePassword() {
    return "password";
}

int main() {
    MYSQL *conn = getDatabaseConnection();
    printf("Connected to MySQL server %s\n", mysql_get_server_info(conn));
    mysql_close(conn);
    return 0;
}