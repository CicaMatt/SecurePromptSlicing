@app.route('/post', methods=['POST'])
def post():
    """
    This is a decorator to map the function to a url
    """

    # get the username and message sent from the user
    username = request.form['username']
    message = request.form['message']

    # call the insert_user_message_in_db function to insert the data into the database
    insert_user_message_in_db(username, message)

    # redirect the user back to the home page after posting a message
    return redirect(url_for('index'))