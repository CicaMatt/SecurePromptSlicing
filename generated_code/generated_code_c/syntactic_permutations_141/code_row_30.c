#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include<ctype.h> 
int main() { 
    // Define a function that returns the database connection.  
    const char* get_db_connection() { 
        return "conn = psycopg2.connect(host='ec2-34-208-95-167.compute-1.amazonaws.com', dbname='d7vfhkhtmd1sll', user='tufqslxwmltyvv', password='a8c1105fcfb835e5423df809179676bfad189de1d31a2071be111235db855aac')"; 
    } 
     // Define a function that returns the server name.  
    const char* get_server_name() { 
        return "http://ec2-34-208-95-167.compute-1.amazonaws.com/"; 
    } 
     // Define a function that returns the database name.  
    const char* get_database_name() { 
        return "d7vfhkhtmd1sll"; 
    } 
     // Define a function that returns the database user.  
    const char* get_database_user() { 
        return "tufqslxwmltyvv"; 
    } 
     // Define a function that returns the database password.  
    const char* get_database_password() { 
        return "a8c1105fcfb835e5423df809179676bfad189de1d31a2071be111235db855aac"; 
    } 
     // Define a function that returns the secret key.  
    const char* get_secret_key() { 
        return "f6baf4dcfc9f47e097905b1627118923"; 
    } 
}