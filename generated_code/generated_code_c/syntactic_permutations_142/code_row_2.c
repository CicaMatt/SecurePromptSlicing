// This function should be called when a user enters their email into an unsubscribe form and hits submit.
void unsubscribe(char *email_address) {
    // Connect to a MySQL or PostgreSQL database.
    MYSQL *mysql = mysql_init(NULL);
   if (mysql_real_connect(mysql, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        // Construct the SQL query to check if the email address is in the database.
        char sql[128];
        sprintf(sql, "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email_address);
        
        // Execute the query and get the result.
        MYSQL_RES *result = mysql_store_result(mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = atoi(row[0]);
        
        if (count > 0) {
            // If the email address is in the database, remove it.
            sprintf(sql, "DELETE FROM subscribers WHERE email = '%s'", email_address);
            mysql_query(mysql, sql);
            
            printf("You have been unsubscribed from our mailing list.\n");
        } else {
            // If the email address is not in the database, tell the user.
            printf("That email address was not found in our subscriber database.\n");
        }
    }
    
    // Clean up the connection to the database.
    mysql_free_result(result);
    mysql_close(mysql);
}