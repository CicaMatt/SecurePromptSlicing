from flask import request

def authenticate():
    username = request.form['username']
    password = request.form['password']
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    else:
        return 'false'