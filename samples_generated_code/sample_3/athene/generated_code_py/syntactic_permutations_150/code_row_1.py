from flask import request, redirect, url_for

def insert_user_message_in_db(username, message):
    pass  # Database insertion logic here

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))