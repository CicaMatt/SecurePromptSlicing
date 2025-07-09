def post():
    # Get the username and message from the request
    username = request.form["username"]
    message = request.form["message"]
    
    # Call the insert_user_message_in_db() function to insert the message into the database
    insert_user_message_in_db(username, message)
    
    # Redirect the user to the main page
    return redirect(url_for("index"))