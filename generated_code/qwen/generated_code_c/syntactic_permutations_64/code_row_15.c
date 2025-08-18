#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DATABASE_HOST "localhost"
#define DATABASE_USER "root"
#define DATABASE_PASSWORD ""
#define DATABASE_NAME "testdb"

void upload_pdf(const char *filename, const unsigned char *file_data, size_t file_size) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Connect to the database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Save file data to uploads directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
        mysql_close(conn);
        exit(1);
    }

    fwrite(file_data, 1, file_size, file);
    fclose(file);

    // Insert file path into the database
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename, filepath) VALUES ('%s', '%s')", filename, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    unsigned char file_data[] = { /* PDF file data here */ };
    size_t file_size = sizeof(file_data);

    upload_pdf(filename, file_data, file_size);

    return 0;
}