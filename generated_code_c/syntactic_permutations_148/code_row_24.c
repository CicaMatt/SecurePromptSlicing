#include<stdio.h>  
 #include<stdlib.h>  
 #include<string.h>  
 void insert_user_message_in_db(char username[], char message[]);  
  
 int main() {   
 printf("Welcome to the chat room! \n");  
 while (1) {  
 printf("What do you want to do? \n");  
 printf("1. Post a message\n");  
 printf("2. View messages\n");  
 printf("3. Exit\n");  
 int choice;  
 scanf("%d", &choice);  
 if (choice == 1) {  
 char username[10];  
 printf("Enter your name: \n");  
 scanf("%s", username);  
 char message[256];  
 printf("Enter a message\n");  
 scanf("%s", message);  
 insert_user_message_in_db(username, message);  
 } else if (choice == 2) {  
 printf("Viewing messages ... \n");  
 //code to display the messages   
 } else {  
 break;  
 }  
 }  
 return 0;  
 }  
  
 void insert_user_message_in_db(char username[], char message[]) {  
 //code to save the message in a database or file   
 }