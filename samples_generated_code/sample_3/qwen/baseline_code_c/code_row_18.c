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
    unsigned long img_size;
    char* img_buffer;

    img_file = fopen(argv[1], "rb");
    if (img_file == NULL)
    {
        fprintf(stderr, "Error opening image file\n");
        mysql_close(con);
        exit(1);
    }

    fseek(img_file, 0, SEEK_END);
    img_size = ftell(img_file);
    rewind(img_file);

    img_buffer = (char*) malloc(sizeof(char) * img_size);
    if (img_buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(img_file);
        mysql_close(con);
        exit(1);
    }

    fread(img_buffer, 1, img_size, img_file);

    char query[2048];
    snprintf(query, sizeof(query), "INSERT INTO images (image) VALUES (%s)", mysql_real_escape_string(con, img_buffer, img_size));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(img_buffer);
    fclose(img_file);
    mysql_close(con);

    return 0;
}