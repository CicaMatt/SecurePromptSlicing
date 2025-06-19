#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"md5.h"
#include"sqlite3.h"

int main(void)
{
    //Declare variables
    char username[20];
    char password[20];
    char hashedPassword[40];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    //hash the entered password
    md5(password, hashedPassword);

    //insert into database
    sqlite3* db;
    int rc = 0;
    char* errMsg = 0;

    rc = sqlite3_open("login.db", &db);

    if(rc)
    {
        printf("Error opening the database: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        char* sqlStatement = "INSERT INTO users (username, password) VALUES ('%s', '%s')";
        sprintf(sqlStatement, username, hashedPassword);
        sqlite3_exec(db, sqlStatement, 0, 0, &errMsg);

        if(errMsg != 0)
        {
            printf("Error inserting data to the database: %s\n", errMsg);
        }
        else
        {
            printf("Data inserted successfully.\n");
        }
    }

    sqlite3_close(db);

    return 0;
}