#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DB_NAME "testdb"
#define UPLOADS_FOLDER "./uploads/"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    FILE *file;
    int length;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    char *filepath = malloc(strlen(UPLOADS_FOLDER) + strlen(filename) + 1);
    strcpy(filepath, UPLOADS_FOLDER);
    strcat(filepath, filename);

    FILE *output_file = fopen(filepath, "wb");
    if (output_file == NULL) {
        perror("File creation failed");
        fclose(file);
        mysql_close(conn);
        free(filepath);
        return;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }
    fclose(file);
    fclose(output_file);

    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    free(filepath);
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}