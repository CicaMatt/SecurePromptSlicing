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

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file-path>\n", argv[0]);
        exit(1);
    }

    FILE *imgFile = fopen(argv[1], "rb");
    if (!imgFile)
    {
        perror("Failed to open file");
        finish_with_error(con);
    }
    
    fseek(imgFile, 0L, SEEK_END);
    long imgSize = ftell(imgFile);
    fseek(imgFile, 0L, SEEK_SET);

    char *imageData = malloc(imgSize + 1);
    if (!imageData)
    {
        perror("Failed to allocate memory");
        fclose(imgFile);
        finish_with_error(con);
    }

    fread(imageData, imgSize, 1, imgFile);
    fclose(imgFile);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES ('%s')", imageData);

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(imageData);
    mysql_close(con);
    exit(0);
}