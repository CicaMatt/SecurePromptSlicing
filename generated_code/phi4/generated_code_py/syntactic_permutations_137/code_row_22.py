from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration.
    # Replace with actual authentication mechanism.
    moderators = {
        "mod_user": {"password": "mod_pass", "session": "mod_session"}
    }
    user_info = moderators.get(username)
    
    if user_info and user_info['password'] == password and user_info['session'] == session:
        return True
    return False

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