#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"
#define UPLOADS_DIR "./uploads/"

void upload_pdf(char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Simulate writing the PDF data to the file
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}

int main() {
    char filename[] = "example.pdf";
    upload_pdf(filename);
    return 0;
}