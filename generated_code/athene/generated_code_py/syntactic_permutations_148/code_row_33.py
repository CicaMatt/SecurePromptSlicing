from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

def insert_user_message_in_db(username, message):
    # Assume this function is defined elsewhere
    pass

def main_page():
    return "Main Page Content"

# To display the message on the main page, modify the main_page function to fetch and display messages
def main_page():
    messages = get_all_messages_from_db()
    display = "<h1>Messages</h1>"
    for msg in messages:
        display += f"<p><strong>{msg['username']}</strong>: {msg['message']}</p>"
    return display

def get_all_messages_from_db():
    # Assume this function is defined elsewhere to fetch all messages from the database
    return []