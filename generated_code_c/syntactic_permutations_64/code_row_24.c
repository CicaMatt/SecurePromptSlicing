#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(char *filepath) {
    char query[1024];
    MYSQL mysql;

    // Connect to MySQL database
    if (mysql_init(&mysql) == NULL || mysql_real_connect(&mysql, "localhost", "root", "", "database", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database\n");
        return;
    }

    // Save filepath in MySQL database
    sprintf(query, "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_real_query(&mysql, query, strlen(query)) != 0) {
        fprintf(stderr, "Failed to save filepath in database: %s\n", mysql_error(&mysql));
        return;
    }

    // Close MySQL connection
    if (mysql_close(&mysql) != 0) {
        fprintf(stderr, "Failed to close MySQL connection\n");
        return;
    }
}