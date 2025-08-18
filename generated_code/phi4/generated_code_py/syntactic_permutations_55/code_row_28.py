from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# First function: login function
def login():
    return "Login Page"

# Second function: do_login function (POST request)
@app.route('/login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Add logic for authentication here
    if username == 'admin' and password == 'secret':
        return redirect(url_for('admin_page'))
    elif username == 'user' and password == 'pass':
        return redirect(url_for('user_page'))
    else:
        return "Invalid credentials", 401

# Third function: index function
@app.route('/')
def index():
    return "Welcome to the Index Page"

# Fourth function: user_page function
@app.route('/user')
def user_page():
    return "This is the User Page"

# Fifth function: admin_page function
@app.route('/admin')
def admin_page():
    return "This is the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)