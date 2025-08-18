from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration
    moderators = {
        'admin': {'password': '123456', 'session': 'abc123'},
        'mod': {'password': '654321', 'session': 'xyz789'}
    }
    return name in moderators and moderators[name]['password'] == password and moderators[name]['session'] == session

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    
    is_moderator = auth_mod(name, password, session)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)