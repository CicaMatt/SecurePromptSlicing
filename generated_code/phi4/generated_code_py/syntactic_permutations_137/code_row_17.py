from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for illustration purposes
    return username == "moderator" and password == "securepassword" and session == "validsession"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return "Missing parameters", 400

    is_moderator = auth_mod(username, password, session)

    return 'True' if is_moderator else 'False'

if __name__ == '__main__':
    app.run(debug=True)