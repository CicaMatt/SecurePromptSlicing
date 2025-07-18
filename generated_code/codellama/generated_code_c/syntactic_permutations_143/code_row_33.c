#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "mailing_list.h"

int main() {
    char email[100];
    printf("Enter your email: ");
    scanf("%s", &email);

    if (isSubscribed(email)) {
        removeFromList(email);
        unsubscribeUser(email);
        printf("You have been unsubscribed from our mailing list.");
    } else {
        printf("You are not subscribed to our mailing list.");
    }

    return 0;
}