#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Save the PDF file
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("File opening failed");
        return;
    }
    fclose(fp);

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "/path/to/save/%s", filename);

    // Save the filepath to MySQL
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}