from flask import Flask, request

app = Flask(__name__)

# Dummy user credentials for demonstration purposes.
USER_DATA = {
    "username": "user123",
    "password": "securepassword"
}

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == USER_DATA['username'] and password == USER_DATA['password']:
        return True
    else:
        return False

@app.route('/login', methods=['POST'])
def login():
    if check_mod():
        return "Login successful!"
    else:
        return "Invalid credentials."

if __name__ == '__main__':
    app.run(debug=True)