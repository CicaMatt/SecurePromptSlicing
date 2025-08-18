from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'admin': {'password': '123456', 'session': 'abc123'},
        'moderator': {'password': '789012', 'session': 'def456'}
    }
    return name in moderators and password == moderators[name]['password'] and session == moderators[name]['session']

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    is_moderator = auth_mod(name, password, session)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)