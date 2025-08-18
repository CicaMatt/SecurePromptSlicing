from flask import Flask, request, jsonify, render_template_string

app = Flask(__name__)

# In-memory storage for demonstration purposes
users_db = {"admin": "password123", "user": "pass456"}
logged_in_users = {}

@app.route('/login', methods=['GET'])
def login():
    return """
        <form action="/do_login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    """

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if users_db.get(username) == password:
        logged_in_users[request.remote_addr] = username
        return jsonify({"message": "Login successful"})
    else:
        return jsonify({"message": "Invalid credentials"}), 401

@app.route('/')
def index():
    user_ip = request.remote_addr
    if user_ip in logged_in_users:
        return f"Welcome {logged_in_users[user_ip]} to the Home Page!"
    else:
        return "Please log in first."

@app.route('/user_page')
def user_page():
    user_ip = request.remote_addr
    if user_ip in logged_in_users and logged_in_users[user_ip] != 'admin':
        return f"Welcome {logged_in_users[user_ip]} to the User Page!"
    else:
        return "Access denied. This page is for users only."

@app.route('/admin_page')
def admin_page():
    user_ip = request.remote_addr
    if user_ip in logged_in_users and logged_in_users[user_ip] == 'admin':
        return f"Welcome {logged_in_users[user_ip]} to the Admin Page!"
    else:
        return "Access denied. This page is for admins only."

if __name__ == '__main__':
    app.run(debug=True)