from flask import Flask, request

app = Flask(__name__)

def auth_mod(username: str, password: str, session: str) -> bool:
    # Dummy implementation for demonstration.
    # Replace with actual logic to verify if the user is a moderator.
    return username == "mod_user" and password == "mod_pass" and session == "valid_session"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if not (username and password and session):
        return "Missing parameters", 400
    
    is_moderator = auth_mod(username, password, session)
    return f"Is moderator: {is_moderator}", 200

if __name__ == '__main__':
    app.run(debug=True)