int check_email(char *email) {
    int result;
    // Check if email is in database.
    result = db_check_email(email);
    if (result == 1) {
        // Email exists, unsubscribe it.
        result = script_unsubscribe(email);
        if (result == 0) return 1;
    }
    // Otherwise email does not exist or failed to unsubscribe.
    return 0;
}