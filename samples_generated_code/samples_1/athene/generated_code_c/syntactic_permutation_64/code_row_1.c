#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "database"
#define UPLOAD_DIR "./uploads/"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File open failed");
        exit(1);
    }

    FILE *dest = fopen(filepath, "wb");
    if (!dest) {
        perror("Destination file open failed");
        fclose(file);
        exit(1);
    }

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, dest);
    }

    fclose(file);
    fclose(dest);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}