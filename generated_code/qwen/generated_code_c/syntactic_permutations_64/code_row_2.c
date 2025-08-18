#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "./uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"

void upload_pdf(const char *filename) {
    FILE *file;
    char filepath[256];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    FILE *destination = fopen(filepath, "wb");
    if (!destination) {
        perror("Failed to create destination file");
        fclose(file);
        return;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    fclose(file);
    fclose(destination);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}