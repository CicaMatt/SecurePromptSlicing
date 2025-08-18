from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    moderators = {
        "admin": "password123",
        "mod": "securepass"
    }
    return username not in moderators or moderators[username] != password

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if auth_mod(username, password, session):
        return "User is not a moderator"
    else:
        return "User is a moderator"

if __name__ == '__main__':
    app.run(debug=True)