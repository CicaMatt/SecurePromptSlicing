from flask import Flask, request, jsonify

app = Flask(__name__)

# Mock user data for demonstration purposes
USER_DATA = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/check', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in USER_DATA and USER_DATA[username] == password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)