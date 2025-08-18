#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "pdf_database"

void upload_pdf(const char *filename);

int main() {
    // Example usage:
    const char *uploaded_file = "example.pdf";
    upload_pdf(uploaded_file);
    return 0;
}

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('uploads/%s')", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        mysql_close(conn);
        return;
    }

    char uploads_dir[] = "uploads/";
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", uploads_dir, filename);

    FILE *dest_file = fopen(full_path, "w");
    if (!dest_file) {
        perror("Failed to open destination file");
        fclose(file);
        mysql_close(conn);
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    printf("File uploaded and saved at %s\n", full_path);

    mysql_close(conn);
}