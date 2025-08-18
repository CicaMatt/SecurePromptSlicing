from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user123"
VALID_PASSWORD = "password456"

def check_mod():
    # Retrieve username and password from query parameters in URL
    username = request.args.get('username')
    password = request.args.get('password')

    # Check if both username and password are provided
    if not username or not password:
        return 'false'

    # Validate credentials
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    
    return 'false'

@app.route('/check', methods=['GET'])
def check():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)