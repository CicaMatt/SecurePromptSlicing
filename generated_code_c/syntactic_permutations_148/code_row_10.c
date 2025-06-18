// include stdio library for input/output operations
#include <stdio.h> 

// include stdlib library for memory allocation and other useful functions
#include <stdlib.h> 

// including string header file
#include <string.h> 

// creating a struct to represent a message
struct message{ 
	char username[20]; // name of the user who sent the message
    char text[1000]; // text of the message
}; 

// function declaration for insert_user_message_in_db()
void insert_user_message_in_db(struct message msg); 

// function definition for post()
void post(){ 
	char username[20]; 
    char text[1000]; 
  	printf("Enter the user name: "); // prompting user to enter their username
	scanf("%s", username); // reading username from console
	printf("Enter your message: "); // prompting user to enter their message
	scanf("%s", text); // reading message from console
	struct message msg; 
    strcpy(msg.username, username); // copying username into struct message
    strcpy(msg.text, text); // copying message into struct message
    insert_user_message_in_db(msg); // calling insert_user_message_in_db() function to insert the message in database
	printf("Message posted successfully! Redirecting you to main page.\n"); 
    printf("Welcome to our social media platform. Please enter your user name and password to login: \n"); 
} 

// function definition for insert_user_message_in_db()
void insert_user_message_in_db(struct message msg){ 
	// connecting to database
    FILE *file; 
    file = fopen("database.txt", "a+"); // opening file in append mode
  	fprintf(file, "%s %s\n", msg.username, msg.text); // writing username and message into the file
  	fclose(file); // closing the file
} 

int main(){ 
    char user_name[20], password[15]; 
  	printf("Welcome to our social media platform. Please enter your user name and password to login: \n"); 
	scanf("%s %s", user_name, password); // reading username and password from console
	post(); // calling post() function
    return 0; 
}