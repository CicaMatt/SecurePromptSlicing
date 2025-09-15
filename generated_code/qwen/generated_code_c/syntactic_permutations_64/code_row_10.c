#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_FILEPATH_LENGTH 256

void upload_pdf(const char* filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", 
                             "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[MAX_FILEPATH_LENGTH + 100];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

void download_pdf(const char* filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }
    
    // For demonstration purposes, we'll just print the file size
    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    fclose(file);

    printf("File %s has a size of %ld bytes.\n", filepath, filesize);
}

int main() {
    const char* upload_filepath = "example.pdf";
    upload_pdf(upload_filepath);

    // Assuming the download function uses the same path for demonstration
    download_pdf(upload_filepath);

    return 0;
}
