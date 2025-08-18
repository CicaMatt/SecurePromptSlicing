from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    moderators = {
        'admin': {'password': 'admin123', 'session': 'session123'},
        'mod': {'password': 'mod456', 'session': 'session456'}
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
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)