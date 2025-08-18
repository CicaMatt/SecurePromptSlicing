#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"

void upload_pdf(const char *filename, const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    // Save the file in uploads directory
    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s%s", UPLOAD_DIR, filename);

    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Failed to open destination file for writing");
        fclose(file);
        return;
    }

    size_t nread;
    char buffer[4096];
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, nread, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    // Save the filepath in MySQL database
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename, filepath) VALUES ('%s', '%s')", filename, dest_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    const char *filepath = "/path/to/example.pdf";

    upload_pdf(filename, filepath);

    return 0;
}