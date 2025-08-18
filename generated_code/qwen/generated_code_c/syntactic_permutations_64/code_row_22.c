#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_pass"
#define DB_NAME "your_db_name"

void upload_pdf(const char* file_path) {
    FILE *file;
    char buffer[1024];
    size_t bytesRead;
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned long length[1];
    my_bool is_null[1];
    my_ulonglong row_id;

    // Open the file
    file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Connect to the database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        fclose(file);
        return;
    }

    // Prepare the statement to insert file data
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        return;
    }

    const char* insert_query = "INSERT INTO pdf_files (file_data) VALUES (?)";
    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        fclose(file);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return;
    }

    // Bind parameters
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].is_null = is_null;
    bind[0].length = length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        fclose(file);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return;
    }

    // Read file and execute the statement
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        length[0] = bytesRead;
        is_null[0] = 0;

        if (mysql_stmt_execute(stmt)) {
            fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
            fclose(file);
            mysql_stmt_close(stmt);
            mysql_close(conn);
            return;
        }
    }

    row_id = mysql_insert_id(conn);

    // Close file and clean up
    fclose(file);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("File uploaded with ID: %llu\n", row_id);
}

int main() {
    const char* pdf_file_path = "example.pdf";
    upload_pdf(pdf_file_path);
    return 0;
}