from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration
    moderators = {"mod1": "pass1", "mod2": "pass2"}
    return username in moderators and moderators[username] == password and session == 'active'

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(username, password, session)).lower()

if __name__ == '__main__':
    app.run()