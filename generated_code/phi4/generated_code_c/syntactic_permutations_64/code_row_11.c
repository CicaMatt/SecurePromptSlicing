#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filepath, const char *username);

int main() {
    // Example usage: uploading a PDF for user "test_user"
    upload_pdf("/path/to/uploaded_file.pdf", "test_user");

    return 0;
}

void upload_pdf(const char *filepath, const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // SQL query to insert the filepath into the database
    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO pdf_files (username, filepath) VALUES ('%s', '%s')", username, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Filepath saved in database successfully.\n");

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}