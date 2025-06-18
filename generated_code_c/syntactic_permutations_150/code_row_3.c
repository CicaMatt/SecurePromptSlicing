void post(request req, response res) {
    // Get username and message from request
    string username = req.get("username");
    string message = req.get("message");

    // Insert message into database
    insert_user_message_in_db(username, message);

    // Redirect user back to main page
    res.redirect("/");
}