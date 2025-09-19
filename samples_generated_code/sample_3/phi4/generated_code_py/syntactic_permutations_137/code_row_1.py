from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Placeholder logic for authentication
    return name == "moderator" and password == "password123" and session == "valid_session"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(name, password, session):
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)