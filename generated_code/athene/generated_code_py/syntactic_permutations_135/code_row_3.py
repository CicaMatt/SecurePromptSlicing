from flask import request

def check_mod():
    username = request.form['username']
    password = request.form['password']
    if username == 'correct_username' and password == 'correct_password':
        return True
    else:
        return False