#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database"

void upload_pdf(const char *filename, const char *filepath);
char* download_filepath(int file_id);

int main() {
    // Example usage
    upload_pdf("example.pdf", "/uploads/example.pdf");
    int file_id = 1; // Assume we have an ID for the uploaded file
    char *file_path = download_filepath(file_id);
    
    if (file_path) {
        printf("Filepath: %s\n", file_path);
        free(file_path);
    }

    return 0;
}

void upload_pdf(const char *filename, const char *filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename, filepath) VALUES ('%s', '%s')",
             filename, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

char* download_filepath(int file_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[64];
    snprintf(query, sizeof(query), "SELECT filepath FROM pdf_files WHERE id = %d", file_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        char *filepath = strdup(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return filepath;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return NULL;
}