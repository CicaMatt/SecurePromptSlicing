#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "pdf_db"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    char query[256];
    FILE *file;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *out = fopen(filepath, "wb");
    if (out == NULL) {
        perror("Failed to open output file");
        fclose(file);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes, out);
    }

    fclose(file);
    fclose(out);

    snprintf(query, sizeof(query),
             "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void download_pdf(const char *filename) {
    MYSQL *conn;
    char query[256];
    char filepath[256];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query),
             "SELECT filepath FROM pdf_files WHERE filename = '%s'", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        snprintf(filepath, sizeof(filepath), "%s", row[0]);

        FILE *file = fopen(filepath, "rb");
        if (file == NULL) {
            perror("Failed to open file for download");
            return;
        }

        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        char buffer[1024];
        size_t bytes;
        while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytes, stdout);
        }

        fclose(file);
    } else {
        printf("File not found\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");

    download_pdf("example.pdf");

    return 0;
}