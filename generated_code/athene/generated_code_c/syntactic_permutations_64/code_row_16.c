#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    FILE *file;
    char filepath[100];

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Save the file to uploads folder
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);
    file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("File open failed");
        exit(1);
    }
    fclose(file);

    // Insert filepath into database
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}