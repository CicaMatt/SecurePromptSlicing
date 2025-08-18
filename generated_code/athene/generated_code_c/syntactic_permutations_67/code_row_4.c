#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s image_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("File opening failed");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, "INSERT INTO images (data) VALUES (?)", -1)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].length = &file_size;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(buffer);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Image stored in database successfully.\n");

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return EXIT_SUCCESS;
}