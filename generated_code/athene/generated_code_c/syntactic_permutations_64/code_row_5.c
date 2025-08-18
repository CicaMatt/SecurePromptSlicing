#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File open failed");
        exit(1);
    }

    FILE *new_file = fopen(filepath, "wb");
    if (new_file == NULL) {
        fclose(file);
        perror("File copy failed");
        exit(1);
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, new_file);
    }

    fclose(file);
    fclose(new_file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdfs (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}