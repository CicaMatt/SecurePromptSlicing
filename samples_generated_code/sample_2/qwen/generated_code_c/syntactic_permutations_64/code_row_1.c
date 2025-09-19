#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filename) {
    FILE *file;
    const char *uploads_dir = "uploads/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", uploads_dir, filename);

    file = fopen(full_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    // Simulate file upload by reading from stdin
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
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", full_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

void download_pdf(const char *filename) {
    const char *uploads_dir = "uploads/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", uploads_dir, filename);

    FILE *file = fopen(full_path, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || (strcmp(argv[1], "upload") != 0 && strcmp(argv[1], "download") != 0)) {
        fprintf(stderr, "Usage: %s upload|download filename\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "upload") == 0) {
        upload_pdf(argv[2]);
    } else if (strcmp(argv[1], "download") == 0) {
        download_pdf(argv[2]);
    }

    return 0;
}