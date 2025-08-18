from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'mod_user': {'password': 'mod_pass', 'session': 'valid_session_id'}
    }
    return (username in moderators and 
            moderators[username]['password'] == password and 
            moderators[username]['session'] == session)

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    is_moderator = auth_mod(username, password, session)
    return str(is_moderator).lower()

@app.route('/check_mod', methods=['GET'])
def check_mod_route():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)