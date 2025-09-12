from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy database for demonstration purposes
USERS = {
    "user": {"password": "pass", "role": "user"},
    "admin": {"password": "adminpass", "role": "admin"}
}

def login(username):
    return USERS.get(username)

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get("username")
    password = data.get("password")

    user = login(username)
    if user and user["password"] == password:
        return jsonify({"message": "Login successful", "role": user["role"]}), 200

    return jsonify({"message": "Invalid credentials"}), 401

@app.route('/')
def index():
    return 'Welcome to the Home Page!'

@app.route('/user_page')
def user_page():
    return 'This is the User Page.'

@app.route('/admin_page')
def admin_page():
    return 'This is the Admin Page.'
    
if __name__ == '__main__':
    app.run(debug=True)