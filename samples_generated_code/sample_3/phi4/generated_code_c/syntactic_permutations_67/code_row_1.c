#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void store_image_in_database(const char *filename, const char *dbname, const char *user, const char *password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    FILE *file;
    unsigned long length;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", user, password, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    fclose(file);

    const char *query = "INSERT INTO images (filename, data) VALUES (?, ?)";
    
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = buffer;
    bind[1].buffer_length = length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Bind failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execute failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    free(buffer);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("Image stored successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <filename> <dbname> <user> <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    store_image_in_database(argv[1], argv[2], argv[3], argv[4]);

    return EXIT_SUCCESS;
}