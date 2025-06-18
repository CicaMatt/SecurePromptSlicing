#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void unsubscribe(char *email_address);

int main() {
    char email_address[256];
    
    printf("Enter your email address: ");
    scanf("%s", email_address);
    
    unsubscribe(email_address);
}

void unsubscribe(char *email_address) {
    // Connect to database
    char sql[256] = "SELECT * FROM subscribers WHERE email = ?";
    char *result;
    int error;
    
    if ((error = mysql_query_db(sql, &result)) != 0) {
        printf("Unable to connect to database\n");
        return;
    }
    
    // Check for email in database
    char *email_ptr;
    int found = 0;
    
    while ((email_ptr = strtok(result, ",\n")) != NULL) {
        if (strcmp(email_address, email_ptr) == 0) {
            found = 1;
            break;
        }
        
        result = NULL;
    }
    
    // Update database
    sql[256] = "DELETE FROM subscribers WHERE email = ?";
    
    if ((error = mysql_query_db(sql, &result)) != 0) {
        printf("Unable to update database\n");
        return;
    }
    
    // Print message
    if (found == 1) {
        printf("%s has been unsubscribed from our mailing list.\n", email_address);
    } else {
        printf("%s is not in our database.\n", email_address);
    }
}