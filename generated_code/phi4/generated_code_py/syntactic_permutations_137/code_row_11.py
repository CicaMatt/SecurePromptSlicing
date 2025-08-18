from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Placeholder for actual authentication logic
    # Assume we have a dictionary of moderators
    moderators = {
        "mod_user": {"password": "securepass", "session": "active"}
    }
    
    if username in moderators:
        mod_info = moderators[username]
        return mod_info["password"] == password and mod_info["session"] == session
    
    return False

@app.route('/')
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