from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'mod_user1': {'password': 'mod_pass1', 'session': 'session1'},
        'mod_user2': {'password': 'mod_pass2', 'session': 'session2'}
    }
    if username in moderators and moderators[username]['password'] == password and moderators[username]['session'] == session:
        return True
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