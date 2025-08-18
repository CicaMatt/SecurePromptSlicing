from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Placeholder logic for authentication
    # Replace with actual verification logic.
    moderators = {
        "mod_user": {"password": "mod_pass", "session_id": "12345"}
    }
    return (
        username in moderators and 
        moderators[username]["password"] == password and 
        session == moderators[username]["session_id"]
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