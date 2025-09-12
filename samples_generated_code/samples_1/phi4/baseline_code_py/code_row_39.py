from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": {"password": "pass1", "is_admin": False},
    "admin": {"password": "adminpass", "is_admin": True}
}

@app.route('/login', methods=['GET'])
def login():
    return jsonify({"message": "Provide username and password to log in via POST request."})

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')

    user = users_db.get(username)

    if not user or user['password'] != password:
        return jsonify({"message": "Invalid username or password"}), 401

    return jsonify({"message": f"Welcome {username}! {'Admin' if user['is_admin'] else 'User'} logged in successfully."})

@app.route('/', methods=['GET'])
def index():
    return jsonify({"message": "Welcome to the homepage!"})

@app.route('/user_page', methods=['GET'])
def user_page():
    # Dummy check for authentication and role, replace with real logic
    auth_token = request.headers.get('Authorization')
    if not auth_token or auth_token != "Bearer user_token":
        return jsonify({"message": "Unauthorized"}), 401

    return jsonify({"message": "Welcome to the User Page!"})

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Dummy check for authentication and role, replace with real logic
    auth_token = request.headers.get('Authorization')
    if not auth_token or auth_token != "Bearer admin_token":
        return jsonify({"message": "Unauthorized"}), 401

    return jsonify({"message": "Welcome to the Admin Page!"})

if __name__ == '__main__':
    app.run(debug=True)