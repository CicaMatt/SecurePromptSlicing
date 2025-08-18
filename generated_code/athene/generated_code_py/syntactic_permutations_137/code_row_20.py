from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Mocked authentication logic for demonstration
    return username == "moderator" and password == "password123" and session == "active"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    is_moderator = auth_mod(username, password, session)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)