#include <stdbool.h>
    
    bool checkUsername(char *username) {
        // Execute a query to check if the username exists in the database
        char sql[256];
        sprintf(sql, "SELECT COUNT(*) FROM users WHERE username='%s'", username);
        
        mysql_query(sql);
        
        // If the username exists return true otherwise return false
        MYSQL_RES *result = mysql_store_result();
        int count = 0;
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                count = atoi(row[0]);
            }
            
            mysql_free_result(result);
        }
        
        return count > 0;
    }