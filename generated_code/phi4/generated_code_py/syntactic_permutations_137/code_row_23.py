from flask import Flask, request

app = Flask(__name__)

def is_moderator(username, password, session):
    # Dummy check for demonstration purposes
    return username == "moderator_user" and password == "secure_password"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    
    if is_moderator(username, password, session):
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == '__main__':
    app.run(debug=True)