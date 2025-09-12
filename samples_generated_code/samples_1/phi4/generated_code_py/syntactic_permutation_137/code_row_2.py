from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Example logic for checking if the user is a moderator
    # Replace with actual authentication mechanism
    moderators = {
        "mod_user": {"password": "modpass", "session": "valid_session"}
    }
    
    return (
        username in moderators and 
        moderators[username]["password"] == password and 
        session == moderators[username]["session"]
    )

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    is_moderator = auth_mod(username, password, session)
    
    return "True" if is_moderator else "False"

if __name__ == '__main__':
    app.run(debug=True)