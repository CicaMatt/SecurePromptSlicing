from flask import request, redirect, url_for, render_template
from your_database_module import insert_user_message_in_db

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

def main_page():
    messages = get_all_messages_from_db()
    return render_template('main.html', messages=messages)

def get_all_messages_from_db():
    # This function should be implemented to fetch all messages from the database
    pass