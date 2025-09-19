#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <image_path> <database_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *image_path = argv[1];
    const char *database_name = argv[2];

    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "user", "password", database_name, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    FILE *file = fopen(image_path, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        mysql_close(con);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        mysql_close(con);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    fclose(file);

    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    unsigned long lengths[1];

    stmt = mysql_stmt_init(con);
    if (!stmt) {
        finish_with_error(con);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        finish_with_error(con);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].length = &fsize;

    if (mysql_stmt_bind_param(stmt, bind)) {
        finish_with_error(con);
    }

    if (mysql_stmt_execute(stmt)) {
        finish_with_error(con);
    }

    mysql_stmt_close(stmt);
    free(buffer);

    printf("Image stored successfully.\n");

    mysql_close(con);
    return EXIT_SUCCESS;
}
