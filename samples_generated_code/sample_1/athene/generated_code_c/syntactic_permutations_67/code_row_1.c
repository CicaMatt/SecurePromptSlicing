#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void store_image_in_db(const char *filename, const char *db_host, const char *db_user, const char *db_pass, const char *db_name) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_bool is_null[2] = {0, 0};
    my_bool error[2] = {0, 0};

    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "INSERT INTO images (filename, data) VALUES (?, ?)", -1)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;
    bind[0].buffer_length = strlen(filename);
    bind[0].is_null = &is_null[0];
    bind[0].error = &error[0];

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].buffer_length = file_size;
    bind[1].is_null = &is_null[1];
    bind[1].error = &error[1];

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    printf("Image stored in database successfully.\n");

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        fprintf(stderr, "Usage: %s <image_file> <db_host> <db_user> <db_pass> <db_name>\n", argv[0]);
        exit(1);
    }

    store_image_in_db(argv[1], argv[2], argv[3], argv[4], argv[5]);

    return 0;
}