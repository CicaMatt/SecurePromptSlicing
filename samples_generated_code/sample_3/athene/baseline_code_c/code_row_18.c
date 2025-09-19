#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; 
    const char *database = "test";

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "Statement preparation failed: %s\n", mysql_error(conn));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;
    bind[0].length = strlen(filename);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].length = length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Binding parameters failed: %s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Statement execution failed: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_stmt_close(stmt);
    free(buffer);
    mysql_close(conn);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        return 1;
    }
    store_image_in_db(argv[1]);
    printf("Image stored successfully in the database.\n");
    return 0;
}