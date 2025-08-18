#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "./uploads/"
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database_name"

void upload_pdf(const char *filename) {
    FILE *source, *destination;
    char source_path[256], destination_path[256];
    snprintf(source_path, sizeof(source_path), "%s", filename);
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_DIR, filename);

    source = fopen(source_path, "rb");
    if (!source) {
        perror("Error opening source file");
        return;
    }

    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Error creating destination file");
        fclose(source);
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        char query[512];
        snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s');", destination_path);
        mysql_query(conn, query);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}