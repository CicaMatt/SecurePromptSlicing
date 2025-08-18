#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filename) {
    FILE *file;
    char buffer[1024];
    const char *upload_folder = "./uploads/";
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "%s%s", upload_folder, filename);

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open the PDF file");
        return;
    }

    FILE *dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        perror("Failed to create the destination file");
        fclose(file);
        return;
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO uploads (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}