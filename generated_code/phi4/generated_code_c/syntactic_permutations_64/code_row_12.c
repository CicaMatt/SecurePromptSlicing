#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void upload_pdf(const char *file_path, const char *db_host, const char *db_user, 
                const char *db_password, const char *db_name) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        exit(1);
    }

    if (!mysql_real_connect(&conn, db_host, db_user, db_password, db_name, 0, 
                            NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (file_path) VALUES ('%s')", file_path);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    printf("PDF file path saved: %s\n", file_path);
    mysql_close(&conn);
}

void download_pdf(const char *file_id, const char *db_host, const char *db_user, 
                  const char *db_password, const char *db_name) {
    MYSQL conn;
    MYSQL_RES *res;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        exit(1);
    }

    if (!mysql_real_connect(&conn, db_host, db_user, db_password, db_name, 0, 
                            NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT file_path FROM pdf_files WHERE id = %s", file_id);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_use_result(&conn);

    while ((row = mysql_fetch_row(res))) {
        printf("Downloading PDF from: %s\n", row[0]);
        // Code to download the file using the path in row[0] would go here
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    const char *file_path = "/path/to/uploaded/file.pdf";
    const char *db_host = "localhost";
    const char *db_user = "username";
    const char *db_password = "password";
    const char *db_name = "database";

    upload_pdf(file_path, db_host, db_user, db_password, db_name);

    const char *file_id = "1"; // Example file ID
    download_pdf(file_id, db_host, db_user, db_password, db_name);

    return 0;
}


Make sure to link with the MySQL client library when compiling:


gcc -o pdf_manager your_program.c $(mysql_config --cflags --libs)