from flask import request

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return auth_mod(username, password, session)

def auth_mod(username, password, session):
    # Mock authentication logic for demonstration purposes
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    if username in moderators:
        mod_info = moderators[username]
        if mod_info['password'] == password and mod_info['session'] == session:
            return True
    return False