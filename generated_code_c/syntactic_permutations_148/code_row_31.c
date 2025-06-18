char* post(request *req) {
    char* username = req->args[0];
    char* message = req->args[1];
    insert_user_message_in_db(username, message);
    return "Location: /";
}