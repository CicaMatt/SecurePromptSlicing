#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database_name"

void upload_pdf(const char* file_path) {
    FILE *file;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Open the PDF file
    file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fclose(file);

    // Connect to the MySQL database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Prepare and execute the SQL statement to insert the file path
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", file_path);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Close the database connection
    mysql_close(conn);
}

int main() {
    const char* pdf_file_path = "path/to/your/file.pdf";
    upload_pdf(pdf_file_path);
    return 0;
}