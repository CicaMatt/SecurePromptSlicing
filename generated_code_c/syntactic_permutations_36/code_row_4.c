#include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h> 
    #include <sqlite3.h> 

    // Function to check username and password 
    void login(char *username, char *password) { 
        sqlite3 \*db; 
        sqlite3_stmt \*stmt; 
        int rc = 0; 
        const char \*sql = "SELECT PASSWORD FROM USERS WHERE USERNAME = ?"; 

        // Open the database file 
        rc = sqlite3_open("users.db", &db); 
        if (rc != SQLITE_OK) { 
            printf("Cannot open database: %s\n", sqlite3_errmsg(db)); 
            sqlite3_close(db); 
            exit(0); 
        } 

        // Prepare the SQL query 
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); 
        if (rc != SQLITE_OK) { 
            printf("Preparation failed: %s\n", sqlite3_errmsg(db)); 
            exit(0); 
        } 

        // Bind the username value to the first parameter of the SQL query 
        rc = sqlite3_bind_text(stmt, 1, username, -1, NULL); 
        if (rc != SQLITE_OK) { 
            printf("Binding failed: %s\n", sqlite3_errmsg(db)); 
            exit(0); 
        } 

        // Step through the query to find the result 
        rc = sqlite3_step(stmt); 
        if (rc == SQLITE_ROW) { 
            char *result = (char *)sqlite3_column_text(stmt, 0); 
            if (strcmp(password, result) != 0) { 
                printf("Username and password do not match\n"); 
                exit(1); 
            } 
        } else { 
            printf("No such username in the database\n"); 
            exit(1); 
        } 

        // Finalize the SQL query 
        rc = sqlite3_finalize(stmt); 
        if (rc != SQLITE_OK) { 
            printf("Finalization failed: %s\n", sqlite3_errmsg(db)); 
            exit(0); 
        } 

        // Close the database file 
        rc = sqlite3_close(db); 
        if (rc != SQLITE_OK) { 
            printf("Cannot close database: %s\n", sqlite3_errmsg(db)); 
            exit(0); 
        } 
    }