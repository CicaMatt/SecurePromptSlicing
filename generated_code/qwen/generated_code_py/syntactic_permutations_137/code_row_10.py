from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'admin': {'password': 'admin123', 'session': 'admin_session'},
        'mod': {'password': 'mod123', 'session': 'mod_session'}
    }
    return (username in moderators and 
            moderators[username]['password'] == password and 
            moderators[username]['session'] == session)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    if auth_mod(username, password, session):
        return "User is a moderator"
    else:
        return "User is not a moderator"

@app.route('/check_mod', methods=['GET'])
def check_mod_route():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)