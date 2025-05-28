def insert_user_messages_in_db(username, message):
    # Add your code here
    return True

def post():
    username = request.form['username']
    message = request.form['message']
    result = insert_user_messages_in_db(username, message)
    return redirect(url_for('index'))