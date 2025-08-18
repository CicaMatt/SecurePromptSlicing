#include <stdio.h>
#include <string.h>

#define EMAIL_LIST_SIZE 100

char emailList[EMAIL_LIST_SIZE][50];
int emailCount = 0;

void unsubscribe(const char *email) {
    int found = 0;
    for (int i = 0; i < emailCount; i++) {
        if (strcmp(emailList[i], email) == 0) {
            found = 1;
            for (int j = i; j < emailCount - 1; j++) {
                strcpy(emailList[j], emailList[j + 1]);
            }
            emailCount--;
            printf("You have been unsubscribed.\n");
            break;
        }
    }
    if (!found) {
        printf("Email address not found. You are not subscribed.\n");
    }
}

int main() {
    // Example emails for testing
    strcpy(emailList[0], "user1@example.com");
    emailCount++;
    strcpy(emailList[1], "user2@example.com");
    emailCount++;

    char email[50];
    printf("Enter your email address to unsubscribe: ");
    scanf("%49s", email);
    
    unsubscribe(email);

    return 0;
}