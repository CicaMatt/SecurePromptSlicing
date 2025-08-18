#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "database_name"

void upload_pdf(const char *filename) {
    // Simulate saving the file to uploads folder
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./uploads/%s", filename);

    FILE *file = fopen(filepath, "w");
    if (file != NULL) {
        fprintf(file, "%s uploaded successfully.\n", filename);
        fclose(file);
    } else {
        perror("Failed to save file");
        exit(EXIT_FAILURE);
    }

    // Save filepath in MySQL database
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Filepath saved to database: %s\n", filepath);

    // Close the connection
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}


**Note:** Ensure that you have a MySQL server running with the appropriate user credentials and database. The `pdf_files` table should exist in your database with at least one column named `filepath`. Adjust the database connection details as necessary.