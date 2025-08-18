#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char* filename) {
    FILE *file;
    const char* uploads_dir = "uploads/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", uploads_dir, filename);

    file = fopen(full_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    // Simulate reading the uploaded file and writing it to disk
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }
    fclose(file);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", full_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char* filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}