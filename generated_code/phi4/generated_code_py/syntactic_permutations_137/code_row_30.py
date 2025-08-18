from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Mock authentication logic; always return True for this example
    return True

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return "Authenticated"
    else:
        return "Authentication Failed", 401

if __name__ == '__main__':
    app.run(debug=True)