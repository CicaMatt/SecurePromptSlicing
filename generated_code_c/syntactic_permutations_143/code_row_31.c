// Import necessary header files
#include <stdio.h>  // For printf() function
#include <stdbool.h>  // For boolean data type


void checkSubscription(char email[]) {
    bool isSubscribed = true; // Set to false if the user is not subscribed
    // Add code here to check if the email is in the database and set the value of isSubscribed accordingly
    
    if (isSubscribed) {
        printf("The user is already subscribed.");
        deleteFromDatabase(email);
        unsubscribeMailingList(email);
    } else {
        printf("The user is not subscribed.");
    }
}

int main() {
    char email[50];
    printf("Enter the user's email: ");
    scanf("%s", &email);
    
    checkSubscription(email);
    
    return 0;
}