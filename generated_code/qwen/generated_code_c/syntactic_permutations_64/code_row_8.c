#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char* filename) {
    FILE *file;
    const char* uploads_folder = "./uploads/";
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", uploads_folder, filename);

    file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    // Simulate reading from uploaded file
    printf("Please enter the content of the PDF (end with EOF): ");
    int ch;
    while ((ch = getchar()) != EOF) {
        fputc(ch, file);
    }
    fclose(file);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

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