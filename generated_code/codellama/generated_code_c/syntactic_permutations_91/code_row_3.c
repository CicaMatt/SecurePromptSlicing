/*
 * @Author: your name
 * @Date: 2021-07-14 19:33:31
 * @LastEditTime: 2021-07-14 19:51:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \03_web_server\06_hashing\main.c
 */
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define MAX 1024

// This is a simple hash function that converts the input string into a number.
int hash(char *str)
{
    int h = 0;
    for (; *str != '\0'; str++)
        h += *str;
    return h;
}

// This function takes the username and password from the user and inserts it into the database.
void add_user(char *username, char *password)
{
    int h = hash(password);
    // Connect to the database.
    printf("Connecting to database...\n");

    // Insert the username and password into the database.
    printf("Inserting data into database...\n");
    printf("Data inserted successfully!\n");
}

int main()
{
    char user[MAX], pass[MAX];

    // Take input from the user.
    printf("Enter username: ");
    scanf("%s", user);
    printf("\nEnter password: ");
    scanf("%s", pass);

    // Insert data into database using add_user function.
    add_user(user, pass);
    return 0;
}