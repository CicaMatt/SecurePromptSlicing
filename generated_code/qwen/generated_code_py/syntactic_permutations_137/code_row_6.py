from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'admin': {'password': 'adminpass', 'session': 'admin_session'},
        'mod1': {'password': 'mod1pass', 'session': 'mod1_session'}
    }
    return (username in moderators and 
            moderators[username]['password'] == password and 
            moderators[username]['session'] == session)

@app.route('/')
def index():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)