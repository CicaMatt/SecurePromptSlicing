from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return jsonify({"message": "Login page"})

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    if not username or not password:
        return jsonify({"error": "Username and password required"}), 400

    # Simulate user authentication (replace with actual logic)
    if username == 'admin' and password == 'secret':
        return jsonify({"message": "Login successful"})
    else:
        return jsonify({"error": "Invalid credentials"}), 401

@app.route('/', methods=['GET'])
def index():
    return jsonify({"message": "Welcome to the homepage"})

@app.route('/user_page', methods=['GET'])
def user_page():
    # Simulate fetching user data (replace with actual logic)
    user_data = {"name": "John Doe", "email": "john@example.com"}
    return jsonify(user_data)

@app.route('/some_other_function', methods=['GET'])
def some_other_function():
    return jsonify({"message": "This is another function"})

if __name__ == '__main__':
    app.run(debug=True)