#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "testdb"
#define UPLOAD_DIR "./uploads/"

void upload_pdf(const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(1);
    }

    // Simulate PDF content being written to the file
    const char *pdf_content = "%PDF-1.4\n..."; // Example PDF content
    fwrite(pdf_content, 1, strlen(pdf_content), file);
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

void download_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT filepath FROM files WHERE filename = '%s'", filename);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        printf("File not found in database.\n");
        mysql_free_result(result);
        mysql_close(conn);
        return;
    }

    const char *filepath = row[0];
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        mysql_free_result(result);
        mysql_close(conn);
        exit(1);
    }

    // Simulate downloading the PDF content
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer); // This would normally be sent over a network
    }
    fclose(file);

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    download_pdf(filename);
    return 0;
}