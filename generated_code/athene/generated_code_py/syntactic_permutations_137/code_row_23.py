from flask import Flask, request

app = Flask(__name__)

def is_moderator(username, password, session):
    # Dummy implementation for demonstration purposes
    return username == 'mod' and password == 'secret' and session == '12345'

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return str(is_moderator(username, password, session)).lower()

if __name__ == '__main__':
    app.run(debug=True)