from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Placeholder logic for authentication, replace with actual checks.
    return username == "moderator" and password == "password123" and session == "active"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)