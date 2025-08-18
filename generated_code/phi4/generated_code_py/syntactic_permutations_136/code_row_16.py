from flask import Flask, request

app = Flask(__name__)

# Predefined credentials for demonstration purposes
USER_CREDENTIALS = {
    "username": "correct_username",
    "password": "correct_password"
}

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username == USER_CREDENTIALS['username'] and password == USER_CREDENTIALS['password']:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)