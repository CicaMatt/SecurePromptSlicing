from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    # Replace with actual authentication logic
    moderators = {
        "admin": {"password": "admin123", "session": "admin_session"},
        "mod": {"password": "mod123", "session": "mod_session"}
    }
    if username in moderators and moderators[username]["password"] == password and moderators[username]["session"] == session:
        return True
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "User is a moderator", 200
    else:
        return "User is not a moderator", 403

if __name__ == '__main__':
    app.run(debug=True)