from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace this with actual authentication logic.
    return username == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return 'Missing parameters', 400

    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return 'User is a moderator'
    else:
        return 'User is not a moderator'

if __name__ == '__main__':
    app.run(debug=True)