#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) 
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (argc < 4)
    {
        printf("Usage: %s <image_file> <db_user> <db_password>\n", argv[0]);
        return 1;
    }

    char *image_file = argv[1];
    const char *user = argv[2];
    const char *password = argv[3];

    if (mysql_real_connect(con, "localhost", user, password, 
                         "testdb", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }    

    FILE *file = fopen(image_file, "rb");
    if (!file)
    {
        perror("Failed to open image file");
        mysql_close(con);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *image_data = malloc(file_size + 1);
    if (!image_data)
    {
        perror("Failed to allocate memory for image data");
        fclose(file);
        mysql_close(con);
        return 1;
    }

    fread(image_data, file_size, 1, file);
    fclose(file);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", "_binary");

    if (mysql_query(con, "SET NAMES binary"))
        finish_with_error(con);

    MYSQL_STMT *stmt;
    MYSQL_BIND param;

    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        free(image_data);
        mysql_close(con);
        return 1;
    }

    const char *insert_query = "INSERT INTO images (image) VALUES (?)";
    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query)))
        finish_with_error(con);

    memset(&param, 0, sizeof(param));

    param.buffer_type = MYSQL_TYPE_BLOB;
    param.buffer = image_data;
    param.buffer_length = file_size;

    if (mysql_stmt_bind_param(stmt, &param))
        finish_with_error(con);

    if (mysql_stmt_execute(stmt))
        finish_with_error(con);

    mysql_stmt_close(stmt);
    free(image_data);
    mysql_close(con);

    return 0;
}