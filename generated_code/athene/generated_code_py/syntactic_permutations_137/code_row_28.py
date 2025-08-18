from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    if username in moderators:
        mod_info = moderators[username]
        return mod_info['password'] == password and mod_info['session'] == session
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    is_moderator = auth_mod(username, password, session)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)