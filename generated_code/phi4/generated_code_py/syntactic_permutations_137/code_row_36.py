from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes.
    # Replace this with actual authentication logic.
    return name == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod')
def check_mod():
    name = request.args.get('name', '')
    password = request.args.get('password', '')
    session = request.args.get('session', '')

    is_moderator = auth_mod(name, password, session)
    return 'True' if is_moderator else 'False'

if __name__ == '__main__':
    app.run(debug=True)