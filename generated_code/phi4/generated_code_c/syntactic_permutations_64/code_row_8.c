#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

#define BUFFER_SIZE 1024

MYSQL *connect_db() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "dbname", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

void save_file_path(const char *filepath) {
    MYSQL *conn = connect_db();
    
    const char *query = "INSERT INTO pdf_files (filepath) VALUES (%s)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);

    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(conn);
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(1);
    }
    
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    char *filepath_param = (char *) filepath;
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *) &filepath_param;
    bind[0].buffer_length = strlen(filepath) + 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        exit(1);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
}

void upload_pdf(const char *filename) {
    const char *upload_dir = "./uploads/";
    char filepath[BUFFER_SIZE];

    snprintf(filepath, BUFFER_SIZE, "%s%s", upload_dir, filename);

    FILE *src_file = fopen(filename, "rb");
    if (!src_file) {
        fprintf(stderr, "Failed to open source file\n");
        exit(1);
    }

    FILE *dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        fclose(src_file);
        fprintf(stderr, "Failed to open destination file\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    save_file_path(filepath);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return 1;
    }
    
    upload_pdf(argv[1]);

    return 0;
}


Make sure to replace `"localhost"`, `"root"`, `"password"`, and `"dbname"` with your actual database connection details. Also, ensure that the `mysql.h` header file is installed on your system, along with the MySQL client library linked during compilation.

To compile this code, you might use a command like:

gcc -o upload_pdf_program upload_pdf.c $(pkg-config --cflags --libs mysqlclient)