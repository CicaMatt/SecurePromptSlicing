//Includes 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>

//Structs
typedef struct {
    char* email;
} User;

//Functions
User get_user();
void unsubscribe(char* email);
void send_message(const char* message, bool error);

int main()
{
    //Get the user
    User user = get_user();

    //Unsubscribe from database
    unsubscribe(user.email);

    return 0;
}

User get_user(){
    User user;

    //Input email address
    char buffer[128];
    printf("Enter your email address: ");
    scanf("%s", buffer);

    //Assign to struct
    user.email = malloc(strlen(buffer)+1);
    strcpy(user.email, buffer);

    return user;
}

void unsubscribe(char* email){
    //Open database
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    
    if (rc != SQLITE_OK) {
        send_message("Database connection failed!", true);
        return;
    } else {
        send_message("Connected to database!", false);
    }

    //Prepare statement
    sqlite3_stmt *res;
    char* sql = "SELECT * FROM users WHERE email=?";
    rc = sqlite3_prepare(db, sql, -1, &res, 0);
    
    if (rc != SQLITE_OK) {
        send_message("Database query failed!", true);
        return;
    } else {
        send_message("Query database succesful!", false);
    }

    //Bind email
    sqlite3_bind_text(res, 1, email, -1, SQLITE_STATIC);
    
    //Execute query
    int step = sqlite3_step(res);
    
    if (step == SQLITE_ROW) {
        send_message("User found in database!", false);
        
        //Delete user from database
        char* sql2 = "DELETE FROM users WHERE email=?";
        rc = sqlite3_prepare(db, sql2, -1, &res, 0);
        sqlite3_bind_text(res, 1, email, -1, SQLITE_STATIC);
        step = sqlite3_step(res);
        
    } else {
        send_message("User not found in database!", true);
    }

    //Close statement
    sqlite3_finalize(res);
    
    //Close database
    sqlite3_close(db);
}

void send_message(const char* message, bool error){
    if (error) {
        printf("Error: %s\n", message);
    } else {
        printf("%s\n", message);
    }
}