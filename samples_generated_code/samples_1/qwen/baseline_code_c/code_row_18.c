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

    if (argc != 3)
    {
        printf("Usage: %s <image_file> <database>\n", argv[0]);
        return 1;
    }

    const char *image_file = argv[1];
    const char *db_name = argv[2];

    FILE *fp = fopen(image_file, "rb");
    if (!fp)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    fseek(fp, 0L, SEEK_END);
    long img_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *img_data = malloc(img_size + 1);
    if (!img_data)
    {
        perror("Failed to allocate memory");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(img_data, img_size, 1, fp);
    fclose(fp);
    
    if (mysql_real_connect(con, "localhost", "user", "password", db_name, 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }  

    mysql_query(con, "DROP TABLE IF EXISTS images");
    mysql_query(con, "CREATE TABLE images(id INT AUTO_INCREMENT PRIMARY KEY, data LONGBLOB)");

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images(data) VALUES(_binary '%s')", img_data);
    
    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    mysql_close(con);
    free(img_data);

    return 0;
}