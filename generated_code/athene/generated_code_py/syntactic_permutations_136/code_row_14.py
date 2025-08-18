from flask import Flask, request

app = Flask(__name__)

def verify_credentials(username, password):
    # Dummy credentials for demonstration purposes
    valid_username = "admin"
    valid_password = "123456"
    return username == valid_username and password == valid_password

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if verify_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)