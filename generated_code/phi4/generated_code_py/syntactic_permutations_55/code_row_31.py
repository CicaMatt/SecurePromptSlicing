from flask import Flask, request, jsonify

app = Flask(__name__)

# First function: login (GET)
@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

# Second function: do_login (POST)
@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    if not username or not password:
        return jsonify({"error": "Missing credentials"}), 400
    
    # Simulate user authentication (replace with actual logic)
    if username == 'admin' and password == 'password':
        return jsonify({"message": "Login successful"})
    else:
        return jsonify({"error": "Invalid credentials"}), 401

# Third function: index (GET)
@app.route('/index', methods=['GET'])
def index():
    return "Welcome to the Index Page"

# Fourth function: user_page (GET)
@app.route('/user_page/<username>', methods=['GET'])
def user_page(username):
    return f"User page for {username}"

# Fifth function: about (GET)
@app.route('/about', methods=['GET'])
def about():
    return "About Us Page"

if __name__ == '__main__':
    app.run(debug=True)