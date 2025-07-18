#include <stdio.h>
    #include <string.h> 
    #include "db_functions.c"

    int main() {
        char email[100];
        printf("Enter an email to unsubscribe: ");
        scanf("%s", email);

        if(isInDatabase(email)){
            deleteFromDatabase(email);
            unsubscribeUser(email);
            printf("%s was deleted from the database and unsubscribed from the mailing list.", email);
        } else {
            printf("%s is not in the database.", email);
        }

        return 0;
    }