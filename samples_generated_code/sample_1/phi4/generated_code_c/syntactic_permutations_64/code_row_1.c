#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int upload_pdf(FILE *pdf_file, const char *filename, MYSQL *conn) {
    char filepath[BUFFER_SIZE] = "uploads/";
    strcat(filepath, filename);

    // Copy the PDF file to the uploads directory
    FILE *output_file = fopen(filepath, "wb");
    if (!output_file) handle_error("Failed to open output file");

    char buffer[8192];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), pdf_file)) > 0) {
        fwrite(buffer, 1, bytes, output_file);
    }

    fclose(output_file);

    // Prepare SQL statement
    const char *query = "INSERT INTO files (filepath) VALUES (%s)";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt) handle_error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        handle_error(mysql_stmt_error(stmt));
    }

    // Bind parameters
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = filepath;
    bind[0].buffer_length = strlen(filepath) + 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        handle_error(mysql_stmt_error(stmt));
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        handle_error(mysql_stmt_error(stmt));
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    const char *hostname = "localhost";
    const char *username = "root";
    const char *password = "your_password";
    const char *database = "your_database";

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, hostname, username, password, database, 0, NULL, 0)) {
        handle_error("Failed to connect to MySQL");
    }

    // Simulate file upload
    FILE *pdf_file = fopen("example.pdf", "rb");
    if (!pdf_file) handle_error("Failed to open PDF file");

    const char *filename = "uploaded_example.pdf";
    upload_pdf(pdf_file, filename, conn);

    fclose(pdf_file);
    mysql_close(conn);
    return 0;
}