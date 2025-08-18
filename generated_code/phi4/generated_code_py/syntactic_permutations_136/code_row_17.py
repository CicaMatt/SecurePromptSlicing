from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def get_credentials_from_url():
    username = request.args.get('username')
    password = request.args.get('password')
    return username, password

def check_credentials(username, password):
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/check_mod')
def check_mod():
    username, password = get_credentials_from_url()
    return check_credentials(username, password)

if __name__ == '__main__':
    app.run(debug=True)