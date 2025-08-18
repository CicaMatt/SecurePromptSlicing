from flask import Flask, request

app = Flask(__name__)

# Replace with your actual username and password for validation.
VALID_USERNAME = "your_username"
VALID_PASSWORD = "your_password"

def check_credentials(username, password):
    return username == VALID_USERNAME and password == VALID_PASSWORD

@app.route('/check_mod')
def check_mod():
    # Extract username and password from the query parameters
    username = request.args.get('username', '')
    password = request.args.get('password', '')

    # Check if credentials are correct
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)