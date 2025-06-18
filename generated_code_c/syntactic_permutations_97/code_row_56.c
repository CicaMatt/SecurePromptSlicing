#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mysql/mysql.h> 

// Function for connection to the database 
MYSQL* connect_db() { 
    MYSQL *conn = mysql_init(NULL); 

    if (!mysql_real_connect(conn, "localhost", "root", "", "mydatabase", 3306, NULL, 0)) { 
        fprintf(stderr, "%s\n", mysql_error(conn)); 
        exit(1); 
    }  
} 

// Function for insertion into the database 
MYSQL_RES* insert_db(MYSQL *conn) { 
    char *username = "johndoe"; 
    char *password = "secretpassword"; // hashed password 
    char *fname = "John"; 
    char *lname = "Doe"; 
    char *email = "johndoe@email.com"; 

    if (mysql_query(conn, "INSERT INTO `users` (`username`, `password`, `first_name`, `last_name`, `email`) VALUES ('" + username + "', '" + password + "', '" + fname + "', '" + lname + "', '" + email + "')")) { 
        fprintf(stderr, "%s\n", mysql_error(conn)); 
        exit(1); 
    }  
} 

// Function for checking if the username is already in the database 
MYSQL_RES* check_db(MYSQL *conn) { 
    char *username = "johndoe"; 

    if (mysql_query(conn, "SELECT `username` FROM `users` WHERE `username` = '" + username + "'")) { 
        fprintf(stderr, "%s\n", mysql_error(conn)); 
        exit(1); 
    }  
} 

int main() { 
    MYSQL *conn; 
    conn = connect_db(); 

    if (check_db(conn)) { 
        printf("Username already exists\n"); 
    } else { 
        insert_db(conn); 
        printf("Successfully registered\n"); 
    }  
}