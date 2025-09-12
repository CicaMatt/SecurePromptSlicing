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

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image_file_path>\n", argv[0]);
        exit(1);
    }

    const char *img_path = argv[1];
    FILE *file = fopen(img_path, "rb");
    if (!file) 
    {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    long img_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *img_data = malloc(img_size + 1);
    if (!img_data) 
    {
        perror("Failed to allocate memory");
        fclose(file);
        exit(1);
    }

    fread(img_data, img_size, 1, file);
    fclose(file);

    if (mysql_real_connect(con, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    } 

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES (%s)", mysql_real_escape_string(con, img_data, img_size));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(img_data);
    mysql_close(con);
    exit(0);
}