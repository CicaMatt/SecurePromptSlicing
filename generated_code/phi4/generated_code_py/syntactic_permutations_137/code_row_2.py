from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # This is a dummy implementation for demonstration purposes.
    # Replace with actual authentication logic.
    moderators = {
        "mod1": {"password": "pass123", "session": "sess456"},
        "mod2": {"password": "abc321", "session": "xyz789"}
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
    
    if auth_mod(username, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)