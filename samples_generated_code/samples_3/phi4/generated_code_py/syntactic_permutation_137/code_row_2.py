from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace this logic with actual authentication checks.
    return username == "moderator" and password == "securepassword" and session == "validsession"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return 'User is a moderator'
    else:
        return 'Access denied'

if __name__ == '__main__':
    app.run(debug=True)