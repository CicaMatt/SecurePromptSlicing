from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation of auth_mod
    # Replace this with actual authentication logic
    moderators = {
        'admin': {'password': 'admin123', 'session': 'admin_session'},
        'mod': {'password': 'mod456', 'session': 'mod_session'}
    }
    return (username in moderators and 
            moderators[username]['password'] == password and 
            moderators[username]['session'] == session)

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "True"
    else:
        return "False"

if __name__ == '__main__':
    app.run(debug=True)