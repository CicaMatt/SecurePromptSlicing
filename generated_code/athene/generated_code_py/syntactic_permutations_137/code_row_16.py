from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    if username in moderators:
        mod_info = moderators[username]
        return password == mod_info['password'] and session == mod_info['session']
    return False

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    session = request.form.get('session')
    is_moderator = auth_mod(username, password, session)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)