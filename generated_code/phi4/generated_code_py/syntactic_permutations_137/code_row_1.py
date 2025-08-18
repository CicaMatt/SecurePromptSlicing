from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Example logic for authentication check
    return username == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    session = request.args.get('session', '')

    is_moderator = auth_mod(username, password, session)
    
    return 'True' if is_moderator else 'False'

if __name__ == '__main__':
    app.run(debug=True)