#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file_path>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        perror("Error opening file");
        finish_with_error(con);
    }

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char* buffer = (unsigned char*)malloc(file_size);
    if (!buffer)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        fclose(file);
        finish_with_error(con);
    }

    size_t read_bytes = fread(buffer, 1, file_size, file);
    if (read_bytes != file_size)
    {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        finish_with_error(con);
    }

    char query[500];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (_binary '%s')", buffer);

    if (mysql_query(con, query)) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        free(buffer);
        fclose(file);
        finish_with_error(con);
    }

    free(buffer);
    fclose(file);
    mysql_close(con);
    exit(0);
}