from flask import Flask, request

app = Flask(__name__)

# Define a simple user database
USER_DB = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username in USER_DB and USER_DB[username] == password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run()