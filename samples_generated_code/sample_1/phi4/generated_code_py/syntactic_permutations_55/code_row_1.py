from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "Login Page"

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username and password:
        # Here you would add authentication logic
        return jsonify({'message': 'Logged in successfully'})
    else:
        return jsonify({'error': 'Invalid credentials'}), 400

@app.route('/', methods=['GET'])
def index():
    return "Welcome to the Index Page"

@app.route('/user_page', methods=['GET'])
def user_page():
    # Assuming user authentication logic is implemented
    return "User Page Content"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Assuming admin authentication logic is implemented
    return "Admin Page Content"

if __name__ == '__main__':
    app.run(debug=True)