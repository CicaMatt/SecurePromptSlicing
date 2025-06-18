#include <stdlib.h>
    #include <mysql/mysql.h>
    #include <string.h>
    #include <stdio.h>

    int upload_pdf(void)
    {
        char filepath[1024];
        char filename[1024];
        FILE *fp;

        // Get the filepath of the pdf file from the user
        printf("Enter the filepath of the PDF file: ");
        scanf("%s", filepath);

        // Save the filepath in the mysql database
        save_filepath(filepath);

        // Open the pdf file and read its contents
        fp = fopen(filepath, "r");
        if (fp == NULL)
        {
            printf("Error: Could not open PDF file\n");
            return 1;
        }

        // Read the contents of the pdf file
        while (fgets(filename, sizeof(filename), fp) != NULL)
        {
            // Do something with the contents of the pdf file
        }

        // Close the pdf file
        fclose(fp);

        return 0;
    }

    int save_filepath(char *filepath)
    {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[1024];

        // Connect to the mysql database
        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0) == NULL)
        {
            printf("Error: Could not connect to MySQL\n");
            return 1;
        }

        // Save the filepath in the mysql database
        sprintf(query, "INSERT INTO files (filepath) VALUES (\"%s\");", filepath);
        if (mysql_query(conn, query))
        {
            printf("Error: Could not save filepath to MySQL\n");
            return 1;
        }

        // Close the mysql connection
        mysql_close(conn);

        return 0;
    }