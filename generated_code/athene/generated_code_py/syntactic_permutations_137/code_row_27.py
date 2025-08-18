from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password):
    # Dummy authentication logic for demonstration
    moderators = {
        'mod1': 'password1',
        'mod2': 'password2'
    }
    return username in moderators and moderators[username] == password

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')  # Session is not used in this example
    if auth_mod(username, password):
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)