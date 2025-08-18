from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {"username": "password"}
is_admin = False

@app.route('/login', methods=['GET'])
def login():
    return jsonify({"message": "Login endpoint accessed via GET"}), 200

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.json.get('username')
    password = request.json.get('password')

    if users.get(username) == password:
        global is_admin
        # In a real-world scenario, check user role to set `is_admin`
        is_admin = (username == 'admin')
        return jsonify({"message": "Login successful"}), 200
    else:
        return jsonify({"error": "Invalid credentials"}), 401

@app.route('/', methods=['GET'])
def index():
    return jsonify({"message": "Welcome to the Index Page"}), 200

@app.route('/user_page', methods=['GET'])
def user_page():
    if is_admin:
        return jsonify({"error": "Access denied as admin"}), 403
    return jsonify({"message": "Welcome to User Page"}), 200

@app.route('/admin_page', methods=['GET'])
def admin_page():
    if not is_admin:
        return jsonify({"error": "Admin access required"}), 403
    return jsonify({"message": "Welcome to Admin Page"}), 200

if __name__ == '__main__':
    app.run(debug=True)