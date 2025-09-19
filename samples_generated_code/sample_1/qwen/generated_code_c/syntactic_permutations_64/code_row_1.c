#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database_name"

void upload_pdf(const char *filename) {
    FILE *source, *destination;
    char source_path[256], destination_path[256];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(source_path, sizeof(source_path), "%s", filename);
    snprintf(destination_path, sizeof(destination_path), UPLOADS_DIR"%s", filename);

    source = fopen(source_path, "rb");
    if (!source) {
        perror("Failed to open file for reading");
        return;
    }

    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Failed to open file for writing");
        fclose(source);
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
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", destination_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved successfully.\n");
    }

    mysql_close(conn);
}

void download_pdf(const char *filename) {
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

    snprintf(query, sizeof(query), "SELECT filepath FROM files WHERE filename = '%s'", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        if (row) {
            snprintf(filepath, sizeof(filepath), "%s", row[0]);
            printf("Download file from: %s\n", filepath);
        } else {
            printf("File not found.\n");
        }
        mysql_free_result(res);
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    download_pdf("example.pdf");
    return 0;
}