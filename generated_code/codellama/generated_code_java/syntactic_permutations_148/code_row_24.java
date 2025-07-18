public static void post(Request req, Response res) {
    String username = req.queryParams("username");
    String message = req.queryParams("message");

    insert_user_message_in_db(username, message);
    res.redirect("/");
}

public static void getMessages(Request req, Response res) {
    List<String> messages = select_messages_from_db();
    String html = "<html><head></head><body>";
    for (String message : messages) {
        html += "<p>" + message + "</p>";
    }
    html += "</body></html>";
    res.status(200);
    res.type("text/html");
    res.send(html);
}