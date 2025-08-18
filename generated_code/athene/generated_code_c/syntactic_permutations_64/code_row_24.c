#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_FILE_PATH 256
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "mydatabase"

void upload_pdf(const char *filename) {
    char file_path[MAX_FILE_PATH];
    snprintf(file_path, sizeof(file_path), "./uploads/%s", filename);

    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    // Assuming the PDF content is received and written here
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", file_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved to database.\n");
    }

    mysql_close(conn);
}

int main() {
    // Example call
    upload_pdf("example.pdf");
    return 0;
}