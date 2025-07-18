#include <stdio.h>
    #include <stdlib.h> 
    #include <string.h> 

    #include "sqlite3.h"  

    // Hashing function
    char hash(char password) {
        int i = 0;
        while (password[i] != '\0') {
            password[i] += 12;
            i++;
        }
        return password; 
    } 

    // Database Connection
    sqlite3_open("user.db", &conn); 

    void createTable() {   
        char sql[] = "CREATE TABLE users (username TEXT, password TEXT)"; 
        sqlite3_exec(conn, sql, 0, 0, 0);
    } 

    // Register User
    int registerUser(char username[16], char password[16]) {   
        sqlite3_stmt stmt; 
        char sql[] = "INSERT INTO users (username, password) VALUES(?,?)"; 
        sqlite3_prepare_v2(conn, sql, -1, &stmt, 0);

        // Hash the password 
        char hashedPassword = hash(password); 

        sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC); 
        sqlite3_bind_text(stmt, 2, hashedPassword, strlen(hashedPassword), SQLITE_STATIC);
    }

    int main() {   
        createTable(); 
        registerUser("John", "1234"); 
        return 0;
    }