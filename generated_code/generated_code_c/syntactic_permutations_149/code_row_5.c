#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

char *get_username(char *query_string);
char *get_message(char *query_string);
void insert_user_message_in_db(char *username, char *message);
void get_messages();
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Please enter a query string\n");
        return -1;
    }
    char *query_string = argv[1];
    
    // Get username and message from the query string
    char *username = get_username(query_string);
    char *message = get_message(query_string);
    // Insert user message in database
    insert_user_message_in_db(username, message);
    
    printf("Content-Type:text/html\r\n\r\n");
    printf("<!DOCTYPE html><html><head><title>Chat Room</title></head><body>\n");
    // Get the messages from the database and display them
    get_messages();
    
    printf("</body></html>");
}

char *get_username(char *query_string) {
    char *key = "username=";
    int key_length = strlen(key);
    // Find the username in the query string
    char *start = strstr(query_string, key);
    if (start == NULL) {
        return "";
    }
    start += key_length;
    char *end = strchr(start, '&');
    int length = end - start;
    
    // Allocate memory for the username and copy it from the query string
    char *username = malloc((length + 1) * sizeof(char));
    strncpy(username, start, length);
    username[length] = '\0';
    
    return username;
}

char *get_message(char *query_string) {
    char *key = "message=";
    int key_length = strlen(key);
    // Find the message in the query string
    char *start = strstr(query_string, key);
    if (start == NULL) {
        return "";
    }
    start += key_length;
    char *end = strchr(start, '&');
    int length = end - start;
    
    // Allocate memory for the message and copy it from the query string
    char *message = malloc((length + 1) * sizeof(char));
    strncpy(message, start, length);
    message[length] = '\0';
    
    return message;
}

void insert_user_message_in_db(char *username, char *message) {
    // Connect to the database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "password", "chat_room", 0, NULL, 0)) {
        printf("Failed to connect to MySQL\n");
        exit(1);
    }
    
    // Prepare the SQL query
    char sql[256];
    sprintf(sql, "INSERT INTO messages VALUES('%s', '%s')", username, message);
    
    // Execute the query
    if (mysql_query(&mysql, sql)) {
        printf("Failed to insert into database\n");
        exit(1);
    }
}

void get_messages() {
    // Connect to the database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "password", "chat_room", 0, NULL, 0)) {
        printf("Failed to connect to MySQL\n");
        exit(1);
    }
    
    // Prepare the SQL query
    char sql[256];
    sprintf(sql, "SELECT * FROM messages");
    
    // Execute the query
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL) {
        printf("Failed to get results from database\n");
        exit(1);
    }
    
    int num_rows = mysql_num_rows(result);
    MYSQL_ROW row;
    // Display the messages in the chat room
    for (int i=0; i<num_rows; i++) {
        row = mysql_fetch_row(result);
        printf("%s: %s<br>\n", row[0], row[1]);
    }
    
    // Free memory
    mysql_free_result(result);
}