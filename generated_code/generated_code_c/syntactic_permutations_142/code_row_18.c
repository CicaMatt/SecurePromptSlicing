#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unsub_db.h"

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    fgets(email, 100, stdin);
    int result = unsubscribe(email);
    if (result == 0) {
        printf("\nEmail address successfully removed!\n");
    } else {
        printf("\nError removing email address from database.\n");
    }
    return 0;
}