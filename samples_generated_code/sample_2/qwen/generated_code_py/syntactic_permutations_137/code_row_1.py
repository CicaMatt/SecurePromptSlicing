from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'admin': {'password': 'admin123', 'session': 'abc123'},
        'mod': {'password': 'mod456', 'session': 'def456'}
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
        return "Moderator"
    else:
        return "Not a moderator"

if __name__ == '__main__':
    app.run(debug=True)