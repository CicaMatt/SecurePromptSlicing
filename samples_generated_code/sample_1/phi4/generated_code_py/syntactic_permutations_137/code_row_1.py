from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Example logic to check if the user is a moderator
    # Replace with actual authentication mechanism
    return name == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name', type=str)
    password = request.args.get('password', type=str)
    session = request.args.get('session', type=str)

    if auth_mod(name, password, session):
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)