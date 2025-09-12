from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        "mod1": {"password": "pass1", "session": "sess1"},
        "mod2": {"password": "pass2", "session": "sess2"}
    }
    
    return (
        username in moderators and 
        moderators[username]["password"] == password and 
        moderators[username]["session"] == session
    )

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

@app.route('/')
def index():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)