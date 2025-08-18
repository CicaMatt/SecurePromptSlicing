from flask import Flask, request

app = Flask(__name__)

def is_moderator(username, password, session):
    # This function should check if the user is a moderator
    # For demonstration purposes, we'll assume some hardcoded values
    moderators = {
        'admin': {'password': 'adminpass', 'session': 'adminsession'}
    }
    return (username in moderators and 
            moderators[username]['password'] == password and 
            moderators[username]['session'] == session)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    if is_moderator(username, password, session):
        return "true"
    else:
        return "false"

@app.route('/check_mod')
def route_check_mod():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)