#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<mysql/mysql.h>
    
    // MySQL credentials
    char *server = "localhost";
    char *username = "root";
    char *password = "password";
    char *database = "mailing_list";
    
    // unsubscribe endpoint code
    void unsubscribe(char *email) {
        if (isInDatabase(email)) {
            deleteFromDatabase(email);
            unsubscribeFromMailingList(email);
            printf("You have been unsubscribed successfully");
        } else {
            printf("Email not found in database");
        }
    }
    
    // checks if email is in the database
    int isInDatabase(char *email) {
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char *query = "SELECT * FROM mailing_list WHERE email=?";
        
        // connect to the MySQL database
        mysql_init(&mysql);
        if (!mysql_real_connect(&mysql, server, username, password, database, 0, NULL, 0)) {
            printf("Error connecting to the MySQL database: %s", mysql_error(&mysql));
            exit(1);
        }
        
        // execute query and get result
        if (mysql_query(&mysql, query)) {
            printf("Error executing query: %s", mysql_error(&mysql));
            exit(1);
        }
        res = mysql_store_result(&mysql);
        
        // check if email is in the database
        while (row = mysql_fetch_row(res)) {
            if (strcmp(email, row[0]) == 0) {
                return 1;
            }
        }
        return 0;
    }
    
    // deletes the user from the database
    void deleteFromDatabase(char *email) {
        MYSQL mysql;
        char *query = "DELETE FROM mailing_list WHERE email=?";
        
        // connect to the MySQL database
        mysql_init(&mysql);
        if (!mysql_real_connect(&mysql, server, username, password, database, 0, NULL, 0)) {
            printf("Error connecting to the MySQL database: %s", mysql_error(&mysql));
            exit(1);
        }
        
        // execute query and get result
        if (mysql_query(&mysql, query)) {
            printf("Error executing query: %s", mysql_error(&mysql));
            exit(1);
        }
    }
    
    // unsubscribes the user from the mailing list
    void unsubscribeFromMailingList(char *email) {
        // code for unsubscribing from the mailing list goes here
        printf("Unsubscribed from mailing list\n");
    }