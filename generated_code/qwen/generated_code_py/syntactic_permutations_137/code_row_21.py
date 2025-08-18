from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # This is a placeholder for actual authentication logic
    # For demonstration purposes, let's assume 'admin' with password 'password123' and any session is a moderator
    return username == 'admin' and password == 'password123'

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "True"
    else:
        return "False"

if __name__ == '__main__':
    app.run(debug=True)