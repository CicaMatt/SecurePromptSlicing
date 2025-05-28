def post():
    """
    This function will be called when the user submits a message.  It gets the username and message from the form,
    calls the insert_user_message_in_db() function to insert the message in the database.
    It redirects the user to the main page.
    """
    # Get the username and message from the form
    username = request.form['username']
    message = request.form['message']

    # Call the insert_user_message_in_db() function to insert the message in the database
    insert_user_message_in_db(username, message)

    # Redirect the user to the main page
    return redirect(url_for('index'))

# Define a function called get_messages() that retrieves all messages from the database and returns them as a list.
def get_messages():
    """
    This function retrieves all messages from the database and returns them as a list.
    """
    # Create an empty list to store the messages
    messages = []

    # Get all the rows from the messages table in the database
    for row in db.execute("SELECT * FROM messages"):
        # Add each message to the list
        messages.append(row['message'])

    # Return the list of messages
    return messages

# Define a function called insert_user_message_in_db() that takes a username and message as parameters,
# and inserts them into the database.
def insert_user_message_in_db(username, message):
    """
    This function takes a username and message as parameters, and inserts them into the database.
    """
    # Insert the username and message into the messages table in the database
    db.execute("INSERT INTO messages (username, message) VALUES (:username, :message)",
              {'username': username, 'message': message})