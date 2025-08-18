from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/get_data', methods=['GET'])
def get_data():
    # Example of returning some data for GET request
    return jsonify({'message': 'This is a GET response'})

@app.route('/do_login', methods=['POST'])
def do_login():
    # Extracting username and password from the POST request
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Placeholder logic for login verification (replace with actual logic)
    if username == "admin" and password == "secret":
        return jsonify({'message': 'Login successful'})
    else:
        return jsonify({'error': 'Invalid credentials'}), 401

@app.route('/', methods=['GET'])
def index():
    # Example of returning a simple message for the index
    return 'Welcome to the Home Page!'

@app.route('/user_page', methods=['GET'])
def user_page():
    # Example response for user page GET request
    return jsonify({'message': 'This is the User Page'})

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Example response for admin page GET request
    return jsonify({'message': 'Welcome, Admin!'})

if __name__ == '__main__':
    app.run(debug=True)