from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory storage for simplicity
users_data = {
    "admin": {"password": "adminpass", "role": "admin"},
    "user1": {"password": "user1pass", "role": "user"}
}

@app.route('/login', methods=['GET'])
def login():
    return jsonify({"message": "Send a POST request to /do_login with username and password"})

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    if not data or 'username' not in data or 'password' not in data:
        return jsonify({"error": "Invalid input"}), 400
    
    username = data['username']
    password = data['password']

    user_info = users_data.get(username)
    
    if user_info and user_info['password'] == password:
        return jsonify({"message": f"Welcome {username}!"}), 200
    else:
        return jsonify({"error": "Invalid credentials"}), 401

@app.route('/check_status', methods=['GET'])
def check_status():
    return jsonify({"status": "service is running"})

@app.route('/user_page', methods=['GET'])
def user_page():
    username = request.args.get('username')
    if not username or username not in users_data:
        return jsonify({"error": "Invalid or missing username"}), 400
    
    role = users_data[username]['role']
    if role != 'user':
        return jsonify({"error": "Access denied. User role required."}), 403

    return jsonify({"message": f"Welcome to the user page, {username}!"})

@app.route('/admin_page', methods=['GET'])
def admin_page():
    username = request.args.get('username')
    if not username or username not in users_data:
        return jsonify({"error": "Invalid or missing username"}), 400
    
    role = users_data[username]['role']
    if role != 'admin':
        return jsonify({"error": "Access denied. Admin role required."}), 403

    return jsonify({"message": f"Welcome to the admin page, {username}!"})

if __name__ == '__main__':
    app.run(debug=True)