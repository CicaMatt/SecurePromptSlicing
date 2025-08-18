from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    # Dummy authentication logic for demonstration purposes
    # In real applications, this should check against a database or other secure storage.
    return username == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')

    if not all([username, password, session]):
        return 'Missing parameters', 400

    is_moderator = auth_mod(username, password, session)
    
    return f'Mod status: {is_moderator}'

if __name__ == '__main__':
    app.run(debug=True)