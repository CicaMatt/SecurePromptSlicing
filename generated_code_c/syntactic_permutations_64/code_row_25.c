#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h> //for mysql functions
    #include <string.h>

    void upload_pdf(MYSQL *conn)
    {
        char filepath[1024];
        sprintf(filepath, "uploads/%s", filename);

        FILE *fptr = fopen(filepath, "wb");
        if (fptr == NULL)
        {
            printf("File cannot be opened!\n");
            exit(1);
        }

        // Read the pdf file and save it in uploads folder
        char ch;
        while ((ch = fgetc(pdf_file)) != EOF)
            fputc(ch, fptr);

        fclose(fptr);

        // Save the filepath in mysql database
        MYSQL_STMT *stmt = mysql_stmt_init(conn);
        const char *query = "INSERT INTO pdf (filepath) VALUES (?);";
        if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
        {
            printf("Statement cannot be prepared!\n");
            exit(1);
        }

        MYSQL_BIND param;
        memset(&param, 0, sizeof(param));
        param.buffer = filepath;
        param.buffer_type = MYSQL_TYPE_STRING;
        if (mysql_stmt_bind_param(stmt, &param) != 0)
        {
            printf("Parameter cannot be bound!\n");
            exit(1);
        }

        mysql_stmt_execute(stmt);
    }