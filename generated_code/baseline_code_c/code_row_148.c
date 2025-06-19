// The post function that is called when the user submits a message
void post(char *username, char *message) {
    // Inserts the message in the database using the insert_user_message_in_db function
    insert_user_message_in_db(username, message);
    // Redirects the user to the main page
    redirect("main.c");
}
// Function that displays the messages
void display_messages() {
    // Creates a list of all the messages from the database
    List *messages = get_all_messages();
    // Prints each message in the list
    for (int i = 0; i < length(messages); i++) {
        printf("%s", messages[i]);
    }
}