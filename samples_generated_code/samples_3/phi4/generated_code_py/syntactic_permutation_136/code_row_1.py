from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes.
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/check_mod')
def check_mod():
    # Extracting username and password from query parameters in the URL
    username = request.args.get('username', '')
    password = request.args.get('password', '')

    # Checking if both username and password match the valid credentials
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)