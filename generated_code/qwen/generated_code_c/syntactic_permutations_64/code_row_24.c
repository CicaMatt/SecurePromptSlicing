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

    FILE *dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        perror("Failed to create file in uploads directory");
        fclose(file);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, dest_file);
    }

    fclose(file);
    fclose(dest_file);

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

int main() {
    upload_pdf("example.pdf");
    return 0;
}