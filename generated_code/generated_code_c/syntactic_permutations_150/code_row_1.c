function post(request, response) {
    username = request.get("username")
    message = request.get("message")
    insert_user_message_in_db(username, message)
    response.redirect("/")
}