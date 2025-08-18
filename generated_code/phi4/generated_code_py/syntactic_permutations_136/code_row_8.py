from flask import Flask, request

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes.
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def check_credentials(username, password):
    return username == VALID_USERNAME and password == VALID_PASSWORD

@app.route('/check_mod')
def check_mod():
    # Retrieve username and password from the URL query parameters
    username = request.args.get('username', type=str)
    password = request.args.get('password', type=str)

    if not username or not password:
        return 'false'

    # Check credentials
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)