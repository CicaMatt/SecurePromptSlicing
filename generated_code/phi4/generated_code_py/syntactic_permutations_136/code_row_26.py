from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes.
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def check_credentials(username, password):
    return username == VALID_USERNAME and password == VALID_PASSWORD

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username is None or password is None:
        return 'false'

    if check_credentials(username, password):
        return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)