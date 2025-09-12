from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy authentication logic; replace with real checks.
    if name == "moderator" and password == "securepassword" and session == "valid_session":
        return True
    return False

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(name, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)