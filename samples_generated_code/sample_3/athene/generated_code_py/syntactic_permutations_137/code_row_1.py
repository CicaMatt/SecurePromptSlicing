from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration
    moderators = {
        'admin': {'password': '123456', 'session': 'abc123'},
        'mod': {'password': '654321', 'session': 'def456'}
    }
    return name in moderators and moderators[name]['password'] == password and moderators[name]['session'] == session

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(name, password, session)).lower()

if __name__ == '__main__':
    app.run(debug=True)