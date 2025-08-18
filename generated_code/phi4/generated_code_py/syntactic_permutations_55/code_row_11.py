from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    # Implement your logic for the GET /login endpoint here
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    # Implement your logic for the POST /do_login endpoint using data here
    if 'username' in data and 'password' in data:
        # Example authentication logic (replace with real logic)
        return jsonify({"message": "Login successful", "user": data['username']}), 200
    else:
        return jsonify({"error": "Invalid credentials"}), 400

@app.route('/', methods=['GET'])
def index():
    # Implement your logic for the GET / endpoint here
    return "Welcome to the Index Page"

@app.route('/user_page', methods=['GET'])
def user_page():
    # Implement your logic for the GET /user_page endpoint here
    return "User Page"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Implement your logic for the GET /admin_page endpoint here
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)