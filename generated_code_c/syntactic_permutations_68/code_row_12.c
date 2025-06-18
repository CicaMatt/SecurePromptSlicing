#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void insert_image(char *name, char *base64) {
        // Connect to database
        MYSQL *con = mysql_init(NULL);
        if (con == NULL) {
            fprintf(stderr, "mysql_init() failed\n");
            return;
        }
    
        // Set up connection parameters
        const char *server = "localhost";
        const char *user = "username";
        const char *password = "password";
        const char *database = "dbname";
    
        if (mysql_real_connect(con, server, user, password, database, 0, NULL, 0) == NULL) {
            fprintf(stderr, "Error: %s\n", mysql_error(con));
            return;
        }
    
        // Insert image into database
        char *query = malloc(256);
        sprintf(query, "INSERT INTO images (name, base64) VALUES ('%s', '%s')", name, base64);
        if (mysql_real_query(con, query, strlen(query)) != 0) {
            fprintf(stderr, "Error: %s\n", mysql_error(con));
            return;
        }
    
        // Clean up
        free(query);
        mysql_close(con);
    }
    
    void upload_image() {
        // Get image name and base64 string from form data
        char *name = get_form_data("name");
        char *base64 = get_form_data("base64");
    
        if (name == NULL || base64 == NULL) {
            return;
        }
    
        // Insert image into database
        insert_image(name, base64);
    }