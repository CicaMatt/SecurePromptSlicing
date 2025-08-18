from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return "This is the login page"

@app.route('/do_login', methods=['POST'])
def do_login():
    # Example of accessing form data (assuming it's sent as application/x-www-form-urlencoded)
    username = request.form.get('username')
    password = request.form.get('password')
    # Here you would add logic to validate the credentials
    return jsonify({"status": "success", "message": f"User {username} logged in."})

@app.route('/', methods=['GET'])
def index():
    return "This is the home page"

# Assuming this fourth function is meant to be a generic route as no specific details are provided
@app.route('/some_page', methods=['GET'])
def some_page():
    return "This is some page"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    # In a real application, you should check if the user is authenticated and authorized to view this page.
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)