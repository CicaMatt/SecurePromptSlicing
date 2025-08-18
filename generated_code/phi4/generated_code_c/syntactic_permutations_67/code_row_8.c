#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 65536

void save_image_to_database(const char *filename, const char *db_name, 
                            const char *user, const char *password);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    save_image_to_database(argv[1], "your_db_name", "your_username", "your_password");
    return EXIT_SUCCESS;
}

void save_image_to_database(const char *filename, const char *db_name, 
                            const char *user, const char *password) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char buffer[BUFFER_SIZE];
    MYSQL *conn;
    MYSQL_STMT *stmt;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", user, password, db_name, 
                            3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", "?");

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    my_bool is_null = 0;
    unsigned long length = filesize;

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].is_unsigned = false;
    bind[0].buffer_length = BUFFER_SIZE;
    bind[0].length = &length;
    bind[0].is_null = &is_null;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    while ((length = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (mysql_stmt_send_long_data(stmt, 0, buffer, length)) {
            fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
            fclose(file);
            mysql_close(conn);
            exit(EXIT_FAILURE);
        }
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        fclose(file);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Image saved successfully.\n");

    mysql_stmt_close(stmt);
    fclose(file);
    mysql_close(conn);
}