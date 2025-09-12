from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return jsonify({"message": "This is the login page."})

@app.route('/do_login', methods=['POST'])
def do_login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    
    if username == 'admin' and password == 'secret':
        return jsonify({"message": "Login successful!"})
    else:
        return jsonify({"message": "Invalid credentials."}), 401

@app.route('/', methods=['GET'])
def index():
    return jsonify({"message": "Welcome to the homepage."})

@app.route('/user_page', methods=['GET'])
def user_page():
    return jsonify({"message": "This is the user page."})

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return jsonify({"message": "This is the admin page."})

if __name__ == '__main__':
    app.run(debug=True)