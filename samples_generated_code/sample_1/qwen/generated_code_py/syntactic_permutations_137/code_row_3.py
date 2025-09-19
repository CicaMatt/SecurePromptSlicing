from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'session1'},
        'mod2': {'password': 'pass2', 'session': 'session2'}
    }
    if username in moderators:
        return moderators[username]['password'] == password and moderators[username]['session'] == session
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)