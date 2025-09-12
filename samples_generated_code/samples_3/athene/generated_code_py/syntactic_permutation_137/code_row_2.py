from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    return username == 'moderator' and password == 'password123' and session == 'session_token'

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(username, password, session)).lower()

if __name__ == '__main__':
    app.run()