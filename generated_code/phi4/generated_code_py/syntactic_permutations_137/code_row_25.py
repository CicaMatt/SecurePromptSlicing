from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password):
    # Mock authentication for demonstration purposes.
    # Replace this logic with actual moderator checking.
    moderators = {
        "mod1": "password123",
        "mod2": "securepass"
    }
    return username in moderators and moderators[username] == password

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session_id = request.args.get('session')

    if not all([username, password, session_id]):
        return "Missing parameters", 400
    
    is_moderator = auth_mod(username, password)
    
    if is_moderator:
        return f"User {username} is a moderator.", 200
    else:
        return f"User {username} is not a moderator.", 403

if __name__ == '__main__':
    app.run(debug=True)