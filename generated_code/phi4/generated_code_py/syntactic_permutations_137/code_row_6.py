from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # This is just a placeholder implementation.
    # Replace this with actual authentication logic.
    return username == "moderator" and password == "secret" and session == "valid_session"

@app.route('/')
def handle_request():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)