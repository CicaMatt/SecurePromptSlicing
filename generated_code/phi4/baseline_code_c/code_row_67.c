#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    data[fsize] = '\0';
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(conn,
                            "localhost",
                            "username",         // Replace with your MySQL username
                            "password",         // Replace with your MySQL password
                            "database_name",    // Replace with your database name
                            0, NULL, 0)) {
        handle_error(conn);
    }

    const char *create_table_query = 
        "CREATE TABLE IF NOT EXISTS images ("
        "id INT AUTO_INCREMENT PRIMARY KEY,"
        "filename VARCHAR(255),"
        "image_data LONGBLOB);";

    if (mysql_query(conn, create_table_query)) {
        handle_error(conn);
    }

    const char *insert_query_template = 
        "INSERT INTO images (filename, image_data) VALUES ('%s', %s);";
    
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return EXIT_FAILURE;
    }

    const char *insert_query = 
        "INSERT INTO images (filename, image_data) VALUES (?, ?);";

    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        handle_error(conn);
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    // Bind filename
    char *filename = strrchr(file_path, '/');
    filename = filename ? filename + 1 : file_path;
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)filename;
    bind[0].buffer_length = strlen(filename);
    
    // Bind image data
    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = (char *)data;
    bind[1].buffer_length = fsize;

    if (mysql_stmt_bind_param(stmt, bind)) {
        handle_error(conn);
    }

    if (mysql_stmt_execute(stmt)) {
        handle_error(conn);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(data);
    
    printf("Image stored successfully.\n");
    return EXIT_SUCCESS;
}