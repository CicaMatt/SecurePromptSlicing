from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes.
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def check_mod():
    # Extract username and password from URL arguments
    username = request.args.get('username')
    password = request.args.get('password')

    # Check if the provided credentials match the valid ones
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/')
def index():
    result = check_mod()
    return result

if __name__ == '__main__':
    app.run(debug=True)