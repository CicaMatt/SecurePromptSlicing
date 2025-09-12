from flask import Flask, request

app = Flask(__name__)

def auth_mod(username: str, password: str, session_id: str) -> bool:
    # Dummy check for demonstration purposes.
    # In practice, replace this with actual authentication logic.
    return username == "moderator" and password == "password123"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    session = request.args.get('session', '')

    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)