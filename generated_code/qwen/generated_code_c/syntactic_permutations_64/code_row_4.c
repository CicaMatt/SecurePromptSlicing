#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"

void upload_pdf(const char *filename) {
    FILE *source, *destination;
    char filepath[256];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open file for reading");
        return;
    }

    destination = fopen(filepath, "wb");
    if (!destination) {
        fclose(source);
        perror("Failed to open file for writing");
        return;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    fclose(source);
    fclose(destination);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
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

void download_pdf(const char *filename) {
    FILE *file;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[512];
    char filepath[256];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    snprintf(query, sizeof(query), "SELECT filepath FROM files WHERE filename='%s'", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    if (!row) {
        printf("File not found in database.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }

    snprintf(filepath, sizeof(filepath), "%s", row[0]);
    file = fopen(filepath, "rb");

    if (!file) {
        perror("Failed to open file for reading");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    download_pdf("example.pdf");
    return 0;
}