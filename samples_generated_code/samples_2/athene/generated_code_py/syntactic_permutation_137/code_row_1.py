from flask import request

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    return username in moderators and moderators[username]['password'] == password and moderators[username]['session'] == session

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return auth_mod(username, password, session)