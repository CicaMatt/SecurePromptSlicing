#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_DIR "./uploads/"
#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    // Save the file to the uploads directory
    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    FILE *dest = fopen(filepath, "wb");
    if (!dest) {
        fclose(src);
        perror("Failed to create destination file");
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }
    fclose(src);
    fclose(dest);

    // Connect to the database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    // Insert filepath into the database
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");

    return 0;
}