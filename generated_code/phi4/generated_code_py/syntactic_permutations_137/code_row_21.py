from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    if username == "moderator" and password == "password123":
        return True
    return False

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    session = request.args.get('session', '')
    
    is_moderator = auth_mod(username, password, session)
    
    if is_moderator:
        return "User is a moderator."
    else:
        return "User is not a moderator."

if __name__ == "__main__":
    app.run()