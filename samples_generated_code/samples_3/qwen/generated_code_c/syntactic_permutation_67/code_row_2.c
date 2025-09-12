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

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    FILE *img_file;
    char query[256];
    char img_data[1024]; // Adjust size as needed
    int img_size;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        exit(1);
    }

    img_file = fopen(argv[1], "rb");
    if (!img_file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(img_file, 0L, SEEK_END);
    img_size = ftell(img_file);
    rewind(img_file);

    if (fread(img_data, sizeof(char), img_size, img_file) != img_size)
    {
        fclose(img_file);
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    fclose(img_file);

    snprintf(query, sizeof(query),
             "INSERT INTO images(data, size) VALUES(%s, %d)",
             mysql_real_escape_string(con, query, img_data, img_size), img_size);

    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }

    mysql_close(con);
    exit(0);
}