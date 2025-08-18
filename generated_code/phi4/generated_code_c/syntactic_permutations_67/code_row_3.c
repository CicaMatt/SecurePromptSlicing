#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *imageFile = argv[1];
    FILE *file = fopen(imageFile, "rb");
    if (!file) error("Error opening file");

    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (!buffer) error("Memory allocation failed");
    
    fread(buffer, sizeof(unsigned char), fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!conn) error("mysql_init() failed");

    if (mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0) == NULL)
        error(mysql_error(conn));

    const char query[] = "INSERT INTO images (image_data) VALUES (?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) error("mysql_stmt_init() failed");

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare(), %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    unsigned long length = fileSize;
    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = buffer;
    bind[0].is_null = 0;
    bind[0].length = &length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param(), %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute(), %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    printf("Image uploaded successfully.\n");

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return 0;
}