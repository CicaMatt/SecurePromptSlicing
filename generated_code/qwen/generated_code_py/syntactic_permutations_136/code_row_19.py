from flask import Flask, request

app = Flask(__name__)

def check_credentials(username, password):
    # Dummy credentials for demonstration purposes
    valid_username = "admin"
    valid_password = "secret"
    return username == valid_username and password == valid_password

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)