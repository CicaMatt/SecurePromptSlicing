#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_FILE_PATH 256

void upload_pdf(const char* filename) {
    FILE *file;
    char filepath[MAX_FILE_PATH];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    FILE *destination = fopen(filepath, "wb");
    if (!destination) {
        perror("Failed to open destination file for writing");
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
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}