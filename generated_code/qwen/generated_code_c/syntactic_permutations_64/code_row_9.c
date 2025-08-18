#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char* filename) {
    FILE *file;
    const char *folder = "uploads/";
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", folder, filename);

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open the file for reading");
        return;
    }

    FILE *dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        perror("Failed to open the destination file for writing");
        fclose(file);
        return;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    const char* filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}