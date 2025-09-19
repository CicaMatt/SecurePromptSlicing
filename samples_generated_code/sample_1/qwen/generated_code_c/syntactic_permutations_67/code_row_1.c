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

    FILE *img_file = fopen("image.jpg", "rb");
    if (!img_file)
    {
        fprintf(stderr, "Cannot open image file\n");
        finish_with_error(con);
    }

    fseek(img_file, 0L, SEEK_END);
    long img_size = ftell(img_file);
    fseek(img_file, 0L, SEEK_SET);

    char *img_data = (char *)malloc(img_size);
    if (!img_data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(img_file);
        finish_with_error(con);
    }

    size_t read_bytes = fread(img_data, sizeof(char), img_size, img_file);
    if (read_bytes != img_size)
    {
        fprintf(stderr, "Error reading file\n");
        free(img_data);
        fclose(img_file);
        finish_with_error(con);
    }

    fclose(img_file);

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, img_data, img_size));

    if (mysql_query(con, query)) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        free(img_data);
        finish_with_error(con);
    }

    free(img_data);
    mysql_close(con);
    exit(0);
}