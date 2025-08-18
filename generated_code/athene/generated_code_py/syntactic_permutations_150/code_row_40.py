from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

def insert_user_message_in_db(username, message):
    # Assume this function is defined elsewhere and works as expected
    pass

def main_page():
    # Assume this function renders the main page
    pass