#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

void check_mysql_error(MYSQL *conn) {
    if (mysql_errno(conn)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <database_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_file = argv[1];
    const char *database_name = argv[2];

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "username", "password", NULL, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    check_mysql_error(conn);
    
    char query[256];
    sprintf(query, "CREATE DATABASE IF NOT EXISTS %s", database_name);
    if (mysql_query(conn, query)) {
        check_mysql_error(conn);
    }
    
    sprintf(query, "USE %s", database_name);
    if (mysql_query(conn, query)) {
        check_mysql_error(conn);
    }

    sprintf(query, 
            "CREATE TABLE IF NOT EXISTS images (\n"
            "id INT AUTO_INCREMENT PRIMARY KEY,\n"
            "image BLOB\n"
            ")");
    if (mysql_query(conn, query)) {
        check_mysql_error(conn);
    }

    FILE *file = fopen(image_file, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char*) malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return EXIT_FAILURE;
    }

    const char *insert_query = "INSERT INTO images (image) VALUES (?)";
    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return EXIT_FAILURE;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    my_ulonglong length = fsize;

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char*) data;
    bind[0].buffer_length = fsize;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return EXIT_FAILURE;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return EXIT_FAILURE;
    }

    printf("Image uploaded successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(data);

    return 0;
}