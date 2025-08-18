from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    # Dummy implementation for login
    return "Login page (GET request)"

@app.route('/submit_data', methods=['POST'])
def submit_data():
    data = request.get_json()
    # Process the submitted data
    return jsonify({"status": "Data received", "data": data})

@app.route('/', methods=['GET'])
def index():
    # Dummy implementation for index
    return "Index page (GET request)"

@app.route('/user_page', methods=['GET'])
def user_page():
    # Dummy implementation for user page
    return "User Page (GET request)"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # Dummy implementation for admin page
    return "Admin Page (GET request)"

if __name__ == '__main__':
    app.run(debug=True)