#include <stdio.h>
#include <mysql/mysql.h>

void store_image(const char *filename) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; 
    const char *database = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        mysql_close(conn);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    fclose(file);

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].length = &file_size;

    const char *query = "INSERT INTO images (image_data) VALUES (?)";
    mysql_stmt_prepare(mysql_stmt_init(conn), query, strlen(query));

    if (mysql_stmt_bind_param(mysql_stmt_init(conn), bind)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        return;
    }

    if (mysql_stmt_execute(mysql_stmt_init(conn))) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        mysql_close(conn);
        return;
    }

    free(buffer);
    printf("Image stored successfully.\n");
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }
    
    store_image(argv[1]);
    return 0;
}