from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace with actual authentication logic.
    return username == "moderator" and password == "securepassword" and session == "validsession"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(username, password, session):
        return 'User is a moderator'
    else:
        return 'User is not a moderator'

if __name__ == '__main__':
    app.run(debug=True)