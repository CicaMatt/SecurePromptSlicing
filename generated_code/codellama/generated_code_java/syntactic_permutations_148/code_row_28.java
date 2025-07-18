public void post(String username, String message) {
    insert_user_message_in_db(username, message);
    redirect("/display-messages");
}