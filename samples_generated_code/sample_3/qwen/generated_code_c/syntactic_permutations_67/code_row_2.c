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

    if (mysql_real_connect(con, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        mysql_close(con);
        exit(1);
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) 
    {
        perror("Failed to open file");
        mysql_close(con);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    long sz = ftell(file);
    rewind(file);

    char *blob_data = malloc(sz + 1);
    fread(blob_data, 1, sz, file);
    fclose(file);

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", mysql_real_escape_string(con, blob_data, sz));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(blob_data);
    mysql_close(con);
    exit(0);
}