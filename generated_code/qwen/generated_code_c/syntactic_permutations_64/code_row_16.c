#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_FOLDER "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "testdb"

void upload_pdf(const char *filename) {
    FILE *source_file, *destination_file;
    char destination_path[256];
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_FOLDER, filename);

    source_file = fopen(filename, "rb");
    if (!source_file) {
        perror("Failed to open the file for reading");
        return;
    }

    destination_file = fopen(destination_path, "wb");
    if (!destination_file) {
        perror("Failed to create file in uploads directory");
        fclose(source_file);
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", destination_path);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("PDF file uploaded and path saved to database.\n");
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf"); // Example usage
    return 0;
}