int checkEmail(char* email) {
    // Check if email exists in database
    if (!databaseContains(email)) {
        return -1;
    }
    
    // Call script to unsubscribe email
    int result = callScript(email);
    
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}