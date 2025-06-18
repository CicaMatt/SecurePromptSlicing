import hashlib
from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)

# User object for storing data
class User():
    def __init__(self, name, email, password):
        self.name = name
        self.email = email
        self.password = password

# List to store user data
users = []

# Route to render login page
@app.route("/login")
def login():
    return "Please enter your credentials"

# Route to process login form submission
@app.route("/process_login", methods=["POST"])
def process_login():
    # Check if user exists in list of users
    for user in users:
        if user.email == request.form['email'] and user.password == hashlib.md5(request.form['password'].encode()).hexdigest():
            session['logged_in'] = True
            session['name'] = user.name
            session['email'] = user.email
            return redirect(url_for('welcome'))
    # If not, return error message
    return "Invalid email or password"

# Route to render registration page
@app.route("/register")
def register():
    return "Please enter your details to register"

# Route to process registration form submission
@app.route("/process_registration", methods=["POST"])
def process_registration():
    # Check if user exists in list of users
    for user in users:
        if user.email == request.form['email']:
            return "Email already registered"
    # If not, add new user to list and return success message
    name = request.form['name']
    email = request.form['email']
    password = hashlib.md5(request.form['password'].encode()).hexdigest()
    users.append(User(name, email, password))
    session['logged_in'] = True
    session['name'] = name
    session['email'] = email
    return redirect(url_for('welcome'))

# Route to render welcome page
@app.route("/welcome")
def welcome():
    if 'logged_in' in session:
        return f"Welcome {session['name']}! You are logged in with email {session['email']}"
    else:
        return redirect(url_for('login'))

# Route to render change email page
@app.route("/change_email")
def change_email():
    if 'logged_in' in session:
        return "Please enter your old and new email addresses"
    else:
        return redirect(url_for('login'))

# Route to process change email form submission
@app.route("/process_change_email", methods=["POST"])
def process_change_email():
    # Check if user exists in list of users and old email matches
    for user in users:
        if user.email == request.form['old_email'] and user.password == hashlib.md5(request.form['password'].encode()).hexdigest():
            user.email = request.form['new_email']
            session['email'] = user.email
            return redirect(url_for('welcome'))
    # If not, return error message
    return "Invalid old email or password"

# Route to render logout page
@app.route("/logout")
def logout():
    session.pop('logged_in', None)
    return redirect(url_for('login'))