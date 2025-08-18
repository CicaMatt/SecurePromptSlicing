from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Example logic for checking if a user is a moderator
    moderators = {
        "moduser1": {"password": "pass123", "session": "sess123"},
        "moduser2": {"password": "pass456", "session": "sess456"}
    }
    
    return (
        username in moderators and 
        moderators[username]["password"] == password and
        moderators[username]["session"] == session
    )

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return "Missing parameters", 400

    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)