from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    if username == 'admin' and password == 'secret':
        return jsonify({'message': 'Login successful'}), 200
    else:
        return jsonify({'message': 'Invalid credentials'}), 401

@app.route('/profile', methods=['GET'])
def profile():
    user_id = request.args.get('user_id')
    if not user_id:
        return "User ID is required", 400
    return f"Profile page for user {user_id}"

@app.route('/user_page', methods=['GET'])
def user_page():
    return "User Page"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)