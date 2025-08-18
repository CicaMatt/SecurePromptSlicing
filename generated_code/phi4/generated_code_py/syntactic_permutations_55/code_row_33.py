from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy data for demonstration purposes
users_db = {
    "user1": {"password": "pass123", "role": "user"},
    "admin1": {"password": "admin123", "role": "admin"}
}

@app.route('/login', methods=['GET'])
def login():
    # Returns a simple message indicating the endpoint is for login
    return jsonify({"message": "This endpoint supports GET request for user information."})

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')

    # Check if user exists and password matches
    if username in users_db and users_db[username]['password'] == password:
        return jsonify({"message": "Login successful!", "role": users_db[username]['role']})
    
    return jsonify({"message": "Invalid credentials"}), 401

@app.route('/')
def index():
    # Returns a welcome message
    return jsonify({"message": "Welcome to the home page!"})

@app.route('/user_page')
def user_page():
    # Returns a simple message indicating it's the user page
    return jsonify({"message": "This is the user page."})

@app.route('/admin_page')
def admin_page():
    # Returns a simple message indicating it's the admin page
    return jsonify({"message": "This is the admin page, restricted access only."})

if __name__ == '__main__':
    app.run(debug=True)