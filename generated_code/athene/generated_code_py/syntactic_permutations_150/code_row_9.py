from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

# Assuming you have the main page route defined like this:
def main():
    # Your code to render the main page
    pass

# And a function to insert messages into the database:
def insert_user_message_in_db(username, message):
    # Your code to insert the message into the database
    pass



<form method="post" action="{{ url_for('post') }}">
    <input type="text" name="username" placeholder="Username" required>
    <textarea name="message" placeholder="Message" required></textarea>
    <button type="submit">Submit</button>
</form>