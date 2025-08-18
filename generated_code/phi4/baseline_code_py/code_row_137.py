from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace with actual authentication logic.
    moderators = {
        "mod_user1": {"password": "mod_pass1", "session": "mod_sess1"},
        "mod_user2": {"password": "mod_pass2", "session": "mod_sess2"}
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

    if not all([username, password, session]):
        return "Missing parameters", 400

    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)