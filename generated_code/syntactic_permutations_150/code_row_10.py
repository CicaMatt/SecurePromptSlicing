def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

<form action="{{ url_for('post') }}" method="POST">
    <label for="username">Username:</label>
    <input type="text" name="username"><br><br>
    <label for="message">Message:</label>
    <textarea name="message"></textarea>
    <br><br>
    <input type="submit" value="Post">
</form>