#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char *file_path) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Database connection parameters
    const char *host = "localhost";
    const char *user = "root";
    const char *pass = "password";
    const char *db = "test_db";

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, db, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Save the file path to the database
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO files (file_path) VALUES ('%s')", file_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char *file_path = "uploads/example.pdf";
    upload_pdf(file_path);
    return 0;
}



-- SQL to create the table (should be run in your MySQL database)
CREATE TABLE IF NOT EXISTS files (
    id INT AUTO_INCREMENT PRIMARY KEY,
    file_path VARCHAR(255) NOT NULL
);