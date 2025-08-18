from flask import Flask, request

app = Flask(__name__)

# Example user data; in a real application, this would be stored securely.
USER_DATA = {
    "username": "user1",
    "password": "pass123"
}

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == USER_DATA['username'] and password == USER_DATA['password']:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)