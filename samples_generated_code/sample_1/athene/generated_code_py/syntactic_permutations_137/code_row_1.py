from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy authentication logic for demonstration
    moderators = {
        'alice': {'password': 'secret123', 'session': 'sess1'},
        'bob': {'password': 'pass456', 'session': 'sess2'}
    }
    if name in moderators:
        mod_info = moderators[name]
        return mod_info['password'] == password and mod_info['session'] == session
    return False

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(name, password, session)).lower()

if __name__ == '__main__':
    app.run(debug=True)