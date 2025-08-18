#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "database"
#define UPLOADS_DIR "./uploads/"

MYSQL *conn;

void upload_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    char new_path[256];
    snprintf(new_path, sizeof(new_path), "%s%s", UPLOADS_DIR, filename);
    FILE *new_file = fopen(new_path, "wb");
    if (new_file == NULL) {
        fclose(file);
        perror("File creation failed");
        return;
    }

    char buffer[1024];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, read_bytes, new_file);
    }

    fclose(file);
    fclose(new_file);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", new_path);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("PDF file uploaded and saved to database successfully.\n");
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf"; // Example usage
    upload_pdf(filename);
    return 0;
}