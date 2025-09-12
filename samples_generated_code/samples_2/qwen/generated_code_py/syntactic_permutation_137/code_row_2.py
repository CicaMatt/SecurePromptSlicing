from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    return username == "moderator" and password == "secret"

@app.route('/')
def index():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "User is a moderator"
    else:
        return "User is not a moderator"

if __name__ == '__main__':
    app.run(debug=True)