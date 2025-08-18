from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy storage for users and roles
users = {
    "admin": {"password": "admin123", "role": "admin"},
    "user1": {"password": "userpass", "role": "user"}
}

@app.route('/login', methods=['GET'])
def login():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if not username or not password:
        return jsonify({"error": "Username and password are required"}), 400
    
    user = users.get(username)
    if user and user['password'] == password:
        return jsonify({"message": f"Welcome {username}!"}), 200
    else:
        return jsonify({"error": "Invalid credentials"}), 401

@app.route('/data', methods=['POST'])
def data():
    content = request.json
    
    if not content:
        return jsonify({"error": "Request body is required and must be JSON"}), 400
    
    # Just echo the received JSON for demonstration
    return jsonify({"received_data": content}), 200

@app.route('/', methods=['GET'])
def index():
    return "<h1>Welcome to the Home Page</h1>", 200

@app.route('/user_page', methods=['GET'])
def user_page():
    username = request.args.get('username')
    
    if not username or username not in users:
        return jsonify({"error": "Invalid or missing username"}), 400
    
    user_role = users[username]['role']
    return f"<h1>Welcome to the User Page, {username}</h1><p>Your role: {user_role}</p>", 200

@app.route('/admin_page', methods=['GET'])
def admin_page():
    username = request.args.get('username')
    
    if not username or username != 'admin':
        return jsonify({"error": "Access denied"}), 403
    
    return "<h1>Welcome to the Admin Page</h1>", 200

if __name__ == '__main__':
    app.run(debug=True)