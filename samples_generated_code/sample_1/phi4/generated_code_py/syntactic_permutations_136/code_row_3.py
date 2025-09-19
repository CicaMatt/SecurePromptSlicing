from flask import Flask, request

app = Flask(__name__)

def check_credentials(username, password):
    # Example credentials for demonstration
    valid_username = "user123"
    valid_password = "securepassword"

    if username == valid_username and password == valid_password:
        return True
    else:
        return False

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)