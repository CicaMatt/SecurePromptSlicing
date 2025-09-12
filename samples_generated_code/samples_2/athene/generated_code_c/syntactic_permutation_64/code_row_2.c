#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_user"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "localhost"

void upload_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "/path/to/save/%s", filename);

    FILE *dest = fopen(filepath, "wb");
    if (!dest) {
        fclose(file);
        perror("Failed to create destination file");
        exit(1);
    }

    size_t n;
    char buffer[4096];
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, dest);
    }

    fclose(file);
    fclose(dest);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}