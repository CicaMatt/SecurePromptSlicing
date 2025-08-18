from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for illustration
    valid_users = {
        "user1": {"password": "pass1", "session": "sess1"},
        "user2": {"password": "pass2", "session": "sess2"}
    }
    return valid_users.get(username) and \
           valid_users[username]["password"] == password and \
           valid_users[username]["session"] == session

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return "Missing parameters", 400
    
    is_authenticated = auth_mod(username, password, session)
    
    return str(is_authenticated)

if __name__ == '__main__':
    app.run(debug=True)