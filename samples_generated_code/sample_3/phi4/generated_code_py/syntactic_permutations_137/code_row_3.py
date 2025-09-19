from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Placeholder for actual authentication logic.
    # This function should be implemented to check against a database or authentication service.
    # For demonstration purposes, returning True if the username is 'moderator'.
    return username == 'moderator' and password == 'password123' and session == 'active_session'

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