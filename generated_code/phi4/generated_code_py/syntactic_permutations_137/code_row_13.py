from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Example logic for checking if a user is a moderator.
    # This should be replaced with actual authentication logic.
    moderators = {
        'mod_user': {'password': 'mod_pass', 'session': 'mod_session'}
    }
    
    return (username in moderators and
            moderators[username]['password'] == password and
            session == moderators[username]['session'])

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not username or not password or not session:
        return "Missing credentials", 400

    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return "User is a moderator", 200
    else:
        return "User is not a moderator", 403

if __name__ == '__main__':
    app.run(debug=True)