#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char* filename, const char* db_host, const char* db_user, const char* db_pass, const char* db_name) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Define upload directory and file path
    const char* upload_dir = "uploads/";
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", upload_dir, filename);

    // Save the PDF file to uploads directory
    FILE* dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        fprintf(stderr, "Failed to open destination file: %s\n", filepath);
        mysql_close(conn);
        exit(1);
    }

    // Here you would read from the uploaded file and write to dest_file
    // For this example, we'll assume the file content is already available in memory or another source

    fclose(dest_file);

    // Insert file path into database
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Close the connection
    mysql_close(conn);
}

int main() {
    const char* filename = "example.pdf";
    const char* db_host = "localhost";
    const char* db_user = "your_db_user";
    const char* db_pass = "your_db_password";
    const char* db_name = "your_database";

    upload_pdf(filename, db_host, db_user, db_pass, db_name);

    return 0;
}