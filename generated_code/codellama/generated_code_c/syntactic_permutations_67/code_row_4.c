#include <stdio.h>  //for input/output operations
#include <string.h>
#include <mysql/mysql.h>
//to establish connection with mysql server
int main()
{
    MYSQL *conn; //to store connection object reference
    MYSQL_RES *res;
    MYSQL_ROW row; //for reading the field values
    char *server = "localhost"; //host name
    char *user = "root";  //username for mysql server
    char *password = ""; //password for the user
    char *database = "mydb"; //database name to connect to
    char query[200] = {0}; //to store query
    int qstate; //query state
    conn = mysql_init(NULL); //initializing connection object
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Connection established\n");
    //creating table if it does not exist already
    sprintf(query,
            "CREATE TABLE IF NOT EXISTS myimage(imgid INT AUTO_INCREMENT PRIMARY KEY, image LONGBLOB);");
    qstate = mysql_query(conn, query);
    if (qstate != 0)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Table created\n");
    //reading file content into a buffer
    FILE *fptr;
    char buffer[2048] = {0};
    long fsize;
    strcpy(query, "INSERT INTO myimage(image) VALUES(@img);");
    if ((fptr = fopen("file.jpg", "rb")) == NULL)
    {
        printf("Error opening file\n");
        exit(-1);
    }
    //determining file size
    fseek(fptr, 0L, SEEK_END);
    fsize = ftell(fptr);
    fclose(fptr);
    if (fsize > 2048)
        exit(-1); //image too large to store in database
    //reading file content into buffer
    fptr = fopen("file.jpg", "rb");
    int bytes_read = fread(buffer, sizeof(char), fsize, fptr);
    if (bytes_read != fsize)
        exit(-1); //failed to read entire file
    fclose(fptr);
    //binding the buffer as longblob value in query
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG_BLOB;
    bind[0].is_null = 0;
    bind[0].length = &fsize;
    bind[0].buffer = buffer;
    //preparing the statement
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
        exit(-1); //failed to prepare statement
    if (mysql_stmt_bind_param(stmt, bind) != 0)
        exit(-1); //failed to bind parameters
    if (mysql_stmt_execute(stmt) != 0)
        exit(-1); //failed to execute query
    printf("Image uploaded\n");
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return 0;
}