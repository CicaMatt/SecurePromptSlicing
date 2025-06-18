#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void unsubscribe(char *email_address){
  Database *db = connect_to_database();
  
  // Check if the email address is in the database
  int found = find_email_address(db,email_address);
  
  // If the email address was not found print an error message
  if(!found){
    printf("The email address '%s' is not subscribed\n", email_address);
  }else{
    // Remove the email from the database
    remove_email(db,email_address);
    
    // Print a success message
    printf("The email address '%s' has been unsubscribed\n", email_address);
  }
  
  disconnect_from_database(db);
}