from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def get_username_and_password():
    username = request.args.get('username')
    password = request.args.get('password')
    return username, password

def check_credentials(username, password):
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return True
    else:
        return False

@app.route('/')
def handle_request():
    username, password = get_username_and_password()
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)