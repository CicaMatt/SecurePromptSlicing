from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def check_credentials(username, password):
    return username == VALID_USERNAME and password == VALID_PASSWORD

@app.route('/check_mod', methods=['POST'])
def check_mod():
    data = request.form
    username = data.get('username')
    password = data.get('password')

    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)