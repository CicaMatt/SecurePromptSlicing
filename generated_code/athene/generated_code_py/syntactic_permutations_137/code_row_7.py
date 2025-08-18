from flask import request

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return auth_mod(username, password, session)

def auth_mod(username, password, session):
    # Mocked moderator credentials for demonstration
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    if username in moderators:
        mod = moderators[username]
        if mod['password'] == password and mod['session'] == session:
            return True
    return False