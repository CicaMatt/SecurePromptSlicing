from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic
    return username == "admin" and password == "secret" and session == "valid_session"

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