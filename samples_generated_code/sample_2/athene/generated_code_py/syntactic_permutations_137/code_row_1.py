from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    mod_info = moderators.get(name)
    if mod_info and mod_info['password'] == password and mod_info['session'] == session:
        return True
    return False

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(auth_mod(name, password, session)).lower()

if __name__ == '__main__':
    app.run()