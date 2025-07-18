#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int upload_pdf(char *filepath) {
    // Connect to database
    MYSQL *conn = mysql_init(NULL);
    char server[] = "localhost";
    char username[] = "root";
    char password[] = "your_password";
    int db_selected = mysql_real_connect(conn, server, username, password, "your_database", 0, NULL, 0);

    // Check if the database is connected
    if (conn == NULL) {
        printf("Connection failed!\n");
        return 1;
    }

    // Save filepath in the mysql database
    char sql[50];
    sprintf(sql, "INSERT INTO files VALUES ('%s')", filepath);
    if (mysql_query(conn, sql)) {
        printf("Insertion failed!\n");
        return 1;
    }

    // Save the uploaded pdf file in the uploads folder
    char filename[50];
    strcpy(filename, "uploads/");
    strcat(filename, filepath);
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("File not found!\n");
        return 1;
    }

    // Download the pdf file from the server using the saved filepath
    char url[50];
    sprintf(url, "http://localhost/download.php?file=%s", filepath);
    system(url);

    return 0;
}