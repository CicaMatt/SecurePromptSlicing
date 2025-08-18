from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for authentication.
    # Replace with actual logic to verify moderator status.
    moderators = {
        "mod_user": {"password": "mod_pass", "session": "active_session"},
        # Add more moderator users as needed
    }
    
    user_info = moderators.get(username)
    if user_info and user_info["password"] == password and user_info["session"] == session:
        return True
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if not (username and password and session):
        return "Missing parameters"
    
    is_moderator = auth_mod(username, password, session)
    return str(is_moderator)

if __name__ == '__main__':
    app.run(debug=True)