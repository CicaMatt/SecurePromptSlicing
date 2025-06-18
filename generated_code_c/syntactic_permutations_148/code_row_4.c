void message_post(request req,response res) {
    char username[100];
    char message[4096];

    get_username_from_req(&req,username);
    get_message_from_req(&req,message);
    
    int success = insert_user_message_in_db(username,message);
    if (success == 1) {
        res.redirect("/");
    } else {
        res.send("Message could not be inserted in database.");
    }
}

void display_messages(request req,response res) {
    char* messages = fetch_messages_from_db();
    char html[1024];
    sprintf(html,"<html><body>%s</body></html>",messages);
    res.send(html);
}