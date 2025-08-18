#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char *file_path) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", 
                             "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (file_path) VALUES ('%s')", file_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void download_pdf(const char *file_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", 
                             "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT file_path FROM pdf_files WHERE id = %s", file_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    if (row != NULL) {
        printf("Downloading: %s\n", row[0]);
        // Here you would add code to actually download or open the file
    } else {
        fprintf(stderr, "No file found with id: %s\n", file_id);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    const char *upload_path = "/path/to/uploads/sample.pdf";
    upload_pdf(upload_path);

    const char *file_id = "1"; // Example ID
    download_pdf(file_id);

    return 0;
}