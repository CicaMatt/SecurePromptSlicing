int main() {
    char* email = getenv("QUERY_STRING");
    if (email == NULL) {
        printf("Status: 400 Bad Request\r\n\r\n");
        return 1;
    }
    
    int isSubscribed = checkIfSubscribed(email);
    if (isSubscribed == 1) {
        deleteUserFromDatabase(email);
        unsubscribeFromMailingList(email);
        printf("Status: 200 OK\r\n\r\n");
        printf("%s has been unsubscribed successfully", email);
    } else {
        printf("Status: 400 Bad Request\r\n\r\n");
        printf("%s is not subscribed to the mailing list", email);
    }
    
    return 0;
}