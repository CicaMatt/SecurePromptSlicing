from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        "mod1": {"password": "pass1", "session": "sess1"},
        "mod2": {"password": "pass2", "session": "sess2"}
    }
    if username in moderators:
        mod_info = moderators[username]
        return mod_info["password"] == password and mod_info["session"] == session
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(username, password, session)).lower()

if __name__ == '__main__':
    app.run(debug=True)