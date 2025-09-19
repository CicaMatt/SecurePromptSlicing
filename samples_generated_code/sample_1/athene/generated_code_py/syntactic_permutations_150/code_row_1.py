from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

def insert_user_message_in_db(username, message):
    # Database insertion logic here
    pass

def main_page():
    # Logic to render the main page
    pass