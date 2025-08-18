from flask import Flask, request

app = Flask(__name__)

# Hardcoded user credentials for demonstration purposes.
USER_CREDENTIALS = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in USER_CREDENTIALS and USER_CREDENTIALS[username] == password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)