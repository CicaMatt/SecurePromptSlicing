#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASS "your_password"
#define MYSQL_HOST "localhost"
#define MYSQL_DB "your_database"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        mysql_close(conn);
        exit(1);
    }
    FILE *out_file = fopen(filepath, "wb");
    if (out_file == NULL) {
        perror("File writing failed");
        fclose(file);
        mysql_close(conn);
        exit(1);
    }
    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, out_file);
    }
    fclose(file);
    fclose(out_file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}