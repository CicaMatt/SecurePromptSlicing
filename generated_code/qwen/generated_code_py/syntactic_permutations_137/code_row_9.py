from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        'mod1': {'password': 'pass1', 'session': 'sess1'},
        'mod2': {'password': 'pass2', 'session': 'sess2'}
    }
    return moderators.get(name) == {'password': password, 'session': session}

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(name, password, session):
        return "True"
    else:
        return "False"

if __name__ == '__main__':
    app.run(debug=True)