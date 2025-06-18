#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    // Structure to store user details
    struct User{
        char* name;
        int age;
        int is_moderator;
    };
    
    // Connect to the database using credentials stored in environment variables
    MYSQL* connect(){
        char* hostname = getenv("DB_HOSTNAME");
        char* username = getenv("DB_USERNAME");
        char* password = getenv("DB_PASSWORD");
        
        // Initialize connection handler
        MYSQL* con = mysql_init(NULL);
        
        // Connect to database
        if(!mysql_real_connect(con, hostname, username, password, NULL, 0, NULL, 0)){
            printf("Error connecting to the database.\n");
            return NULL;
        }
        else{
            printf("Connected to the database successfully.\n");
            return con;
        }
    }
    
    // Execute a query to check if user is moderator
    int is_moderator(MYSQL* con, char* name){
        char* query = "SELECT is_moderator FROM users WHERE name='%s'";
        
        // Replace %s with user name
        query = mysql_real_escape_string(con, query);
        
        // Execute the query
        if(mysql_query(con, query)){
            printf("Error executing the query.\n");
            return 0;
        }
        
        // Store result of the query
        MYSQL_RES* res = mysql_store_result(con);
        
        // Check if there are any rows returned by the query
        if(mysql_num_rows(res) == 0){
            printf("User not found.\n");
            return 0;
        }
        
        // Fetch row from result set
        MYSQL_ROW row = mysql_fetch_row(res);
        
        // Check if user is moderator
        int is_moderator = atoi(row[0]);
        
        return is_moderator;
    }
    
    int main(){
        // Connect to the database
        MYSQL* con = connect();
        
        // Get name of user from command line arguments
        char* name = argv[1];
        
        // Check if user is moderator
        int is_moderator = is_moderator(con, name);
        
        // Print result
        printf("%s is a moderator: %d\n", name, is_moderator);
        
        return 0;
    }