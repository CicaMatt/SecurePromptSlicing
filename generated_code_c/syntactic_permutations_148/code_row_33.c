// Importing header files
#include<stdio.h> 
  
// Function to insert a message into a table called 'messages'
void insert_user_message_in_db(char *username, char *msg){
    char sql[1024] = {0}; // SQL query buffer
    sprintf(sql,"INSERT INTO messages (username, msg) VALUES ('%s','%s');", username, msg); // building SQL query
    mysql_query(sql); // Execute the query
}

// Function to display all messages from the database table called 'messages'
void show_all_msgs() {
    char sql[1024] = {0}; // SQL query buffer
    sprintf(sql,"SELECT * FROM messages;"); // building SQL query
    MYSQL_RES *result = mysql_query(sql); // Execute the query
  
    while (MYSQL_ROW row = mysql_fetch_assoc(result)) {
        printf("%s: %s\n",row[0],row[1]); // Printing the username and message
    }
}

// Function to handle POST request
void post() {
    char *username,*msg; 
  
    // Getting the username and message from the request
    sscanf(getenv("REQUEST_METHOD"),"%s",&username);
    sscanf(getenv("QUERY_STRING"),"msg=%s",&msg);
    
    insert_user_message_in_db(username, msg); // inserting the message into database
  
    // Redirecting user to main page
    printf("Status: 302 Found\n");
    printf("Location:/main.php\n\n");
}
  
int main() {
    char *request_uri = getenv("REQUEST_URI"); 
    if(strcmp(request_uri, "/post.php")==0){ // If the request URI is /post.php
        post(); // handle the POST request
    } else {
        show_all_msgs(); // Display all messages from database table called 'messages'
    }
}