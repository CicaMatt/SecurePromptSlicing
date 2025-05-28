def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

<form action="{{ url_for('post') }}" method="post">
    <input type="text" name="username">  
    <input type="text" name="message">  
    <input type="submit" value="Post">
</form>