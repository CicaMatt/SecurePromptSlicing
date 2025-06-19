// Import necessary libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <sqlite3.h> 
    
    int insert_user_message_in_db(char *username, char *message) {
        sqlite3 *db;
        char *error_message = 0;
        int result;
    
        // Open the database
        result = sqlite3_open("database.db", &db);
        if (result != SQLITE_OK) {
            printf("Error opening the database: %s\n", error_message);
            return 1;
        }
        
        // Prepare SQL statement
        char *sql = "INSERT INTO Messages(username, message) VALUES(?, ?)";
        sqlite3_stmt *statement;
        result = sqlite3_prepare(db, sql, -1, &statement, 0);
        if (result != SQLITE_OK) {
            printf("Error preparing the statement: %s\n", error_message);
            return 2;
        }
        
        // Bind values to the parameters
        sqlite3_bind_text(statement, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, message, -1, SQLITE_STATIC);
    
        // Execute statement and check for errors
        result = sqlite3_step(statement);
        if (result != SQLITE_DONE) {
            printf("Error executing the statement: %s\n", error_message);
            return 3;
        }
        
        // Finalize and close database
        sqlite3_finalize(statement);
        result = sqlite3_close(db);
        if (result != SQLITE_OK) {
            printf("Error closing the database: %s\n", error_message);
            return 4;
        }
        
        // Return success
        return 0;
    }
    
    void post() {
        char username[128];
        char message[1024];
    
        // Get the username and message from the request
        printf("Username: ");
        fgets(username, sizeof username, stdin);
        printf("Message: ");
        fgets(message, sizeof message, stdin);
        
        // Call insert_user_message_in_db() to insert the message into the database
        result = insert_user_message_in_db(username, message);
        if (result != 0) {
            printf("Error inserting the user message in the database\n");
            return;
        }
        
        // Redirect the user back to the main page
        printf("You have successfully posted a message. You will now be redirected to the main page.\n");
    }