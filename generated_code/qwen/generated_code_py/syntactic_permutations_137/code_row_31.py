from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'admin': {'password': 'secret', 'session': '12345'},
        'mod': {'password': 'modpass', 'session': '67890'}
    }
    if name in moderators and moderators[name]['password'] == password and moderators[name]['session'] == session:
        return True
    return False

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(name, password, session):
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)