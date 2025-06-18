#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

void upload_pdf(char *file) {
    int n;
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // Connect to the MySQL database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to MySQL: %s\n", mysql_error());
        exit(1);
    }

    // Insert the file into the database
    char query[256];
    sprintf(query, "INSERT INTO uploads (file) VALUES ('%s')", file);
    if (mysql_query(&mysql, query)) {
        fprintf(stderr, "Failed to insert into table: %s\n", mysql_error());
        exit(1);
    }

    // Download the file from the database
    sprintf(query, "SELECT file FROM uploads WHERE id = 1");
    MYSQL_RES *res = mysql_store_result(&mysql);
    while (MYSQL_ROW row = mysql_fetch_row(res)) {
        n = atoi(row[0]);
        printf("File %d: %s\n", n, file);
    }
    mysql_free_result(res);

    // Close the database connection
    mysql_close(&mysql);
}