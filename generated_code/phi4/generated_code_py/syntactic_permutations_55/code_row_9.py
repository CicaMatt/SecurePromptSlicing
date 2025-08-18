from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy storage for users
users = {
    "user1": {"password": "pass1"},
    "admin": {"password": "adminpass"}
}

def login(username: str, password: str) -> bool:
    user = users.get(username)
    if user and user["password"] == password:
        return True
    return False

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get("username")
    password = data.get("password")
    if login(username, password):
        return jsonify({"message": "Login successful"}), 200
    return jsonify({"error": "Invalid credentials"}), 401

@app.route('/')
def index():
    return "Welcome to the homepage!"

@app.route('/user_page')
def user_page():
    return "This is the user page."

@app.route('/admin_page')
def admin_page():
    return "This is the admin page."

if __name__ == '__main__':
    app.run(debug=True)