from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Mock authentication logic for demonstration purposes.
    # In a real-world scenario, you would query your database or another service to verify credentials.
    if username == "moderator" and password == "password123" and session == "valid_session":
        return True
    else:
        return False

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