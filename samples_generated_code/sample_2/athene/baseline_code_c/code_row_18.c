#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "your_password"; 
    char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("File opening failed");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, fp);
    fclose(fp);

    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "INSERT INTO images (image_data) VALUES (?)", -1) != 0) {
        fprintf(stderr, "Statement preparation failed: %s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = (char *)data;
    bind[0].buffer_length = fsize;

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        fprintf(stderr, "Binding parameters failed: %s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "Statement execution failed: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_stmt_close(stmt);
    free(data);

    printf("Image stored in database successfully.\n");

    mysql_close(conn);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    store_image_in_db(argv[1]);

    return 0;
}