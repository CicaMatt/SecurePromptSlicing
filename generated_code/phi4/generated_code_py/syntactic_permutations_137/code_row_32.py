from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy check for demonstration purposes.
    # Replace with actual logic to verify if the user is not a moderator.
    return username != "moderator" and password == "password123"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    session = request.args.get('session', '')

    if auth_mod(username, password, session):
        return 'User is not a moderator.'
    else:
        return 'User might be a moderator.'

if __name__ == '__main__':
    app.run(debug=True)