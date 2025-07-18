import re
from flask import Flask, request
from passlib.hash import sha256_crypt
from datetime import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'

users = [{
    'id': 1,
    'email': 'user@example.com',
    'password': 'passw0rd'
}]


def validate_signup(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    elif len(dict['password']) < 8:
        return False, "Password must be at least 8 characters long"
    return True, None


def validate_login(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    elif len(dict['password']) < 8:
        return False, "Password must be at least 8 characters long"
    return True, None


def validate_change_email(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['old_email']):
        return False, "Invalid email address"
    elif len(dict['new_email']) < 8:
        return False, "Email must be at least 8 characters long"
    elif not re.match(r'[^@]+@[^@]+\.[^@]+', dict['new_email']):
        return False, "Invalid email address"
    elif len(dict['password']) < 8:
        return False, "Password must be at least 8 characters long"
    return True, None


def validate_change_password(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    elif len(dict['old_password']) < 8:
        return False, "Old password must be at least 8 characters long"
    elif len(dict['new_password']) < 8:
        return False, "New password must be at least 8 characters long"
    elif not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    return True, None


def validate_forgot_password(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    elif len(dict['password']) < 8:
        return False, "Password must be at least 8 characters long"
    return True, None


def validate_reset_password(dict):
    if not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    elif len(dict['new_password']) < 8:
        return False, "New password must be at least 8 characters long"
    elif not re.match(r'[^@]+@[^@]+\.[^@]+', dict['email']):
        return False, "Invalid email address"
    return True, None


def get_user_by_email(email):
    for user in users:
        if user['email'] == email:
            return user
    return None


def get_user_by_id(user_id):
    for user in users:
        if user['id'] == user_id:
            return user
    return None


@app.route('/signup', methods=['GET', 'POST'])
def signup():
    if request.method == 'POST':
        email = request.form['email']
        password = sha256_crypt.encrypt(str(request.form['password']))
        is_valid, message = validate_signup({'email': email, 'password': password})
        if not is_valid:
            return message
        users.append({'id': len(users) + 1,
                      'email': email,
                      'password': password})
        return "User created successfully"
    return '''<form method="post">
                <input type=email name=email>
                <input type=password name=password>
                <input type=submit value=Signup>
              </form>'''


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = sha256_crypt.encrypt(str(request.form['password']))
        is_valid, message = validate_login({'email': email, 'password': password})
        if not is_valid:
            return message
        user = get_user_by_email(email)
        if not user:
            return "User doesn't exist"
        elif user['password'] != password:
            return "Invalid credentials"
        return "Logged in successfully"
    return '''<form method="post">
                <input type=email name=email>
                <input type=password name=password>
                <input type=submit value=Login>
              </form>'''


@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = sha256_crypt.encrypt(str(request.form['password']))
        is_valid, message = validate_change_email({'old_email': old_email,
                                                   'new_email': new_email,
                                                   'password': password})
        if not is_valid:
            return message
        user = get_user_by_email(old_email)
        if not user:
            return "User doesn't exist"
        elif user['password'] != password:
            return "Invalid credentials"
        users[users.index({'id': user['id'], 'email': old_email})] = {
            'id': user['id'],
            'email': new_email,
            'password': user['password']}
        return "Email changed successfully"
    return '''<form method="post">
                <input type=email name=old_email>
                <input type=email name=new_email>
                <input type=password name=password>
                <input type=submit value=Change Email>
              </form>'''


@app.route('/change-password', methods=['GET', 'POST'])
def change_password():
    if request.method == 'POST':
        email = request.form['email']
        old_password = sha256_crypt.encrypt(str(request.form['old_password']))
        new_password = sha256_crypt.encrypt(str(request.form['new_password']))
        is_valid, message = validate_change_password({'email': email,
                                                      'old_password': old_password,
                                                      'new_password': new_password})
        if not is_valid:
            return message
        user = get_user_by_email(email)
        if not user:
            return "User doesn't exist"
        elif user['password'] != old_password:
            return "Invalid credentials"
        users[users.index({'id': user['id'], 'email': email})] = {
            'id': user['id'],
            'email': user['email'],
            'password': new_password}
        return "Password changed successfully"
    return '''<form method="post">
                <input type=email name=email>
                <input type=password name=old_password>
                <input type=password name=new_password>
                <input type=submit value=Change Password>
              </form>'''


@app.route('/forgot-password', methods=['GET', 'POST'])
def forgot_password():
    if request.method == 'POST':
        email = request.form['email']
        password = sha256_crypt.encrypt(str(request.form['password']))
        is_valid, message = validate_forgot_password({'email': email,
                                                      'password': password})
        if not is_valid:
            return message
        user = get_user_by_email(email)
        if not user:
            return "User doesn't exist"
        users[users.index({'id': user['id'], 'email': email})] = {
            'id': user['id'],
            'email': user['email'],
            'password': password}
        return "Password changed successfully"
    return '''<form method="post">
                <input type=email name=email>
                <input type=password name=password>
                <input type=submit value=Forgot Password>
              </form>'''


@app.route('/reset-password', methods=['GET', 'POST'])
def reset_password():
    if request.method == 'POST':
        email = request.form['email']
        new_password = sha256_crypt.encrypt(str(request.form['new_password']))
        is_valid, message = validate_reset_password({'email': email,
                                                     'new_password': new_password})
        if not is_valid:
            return message
        user = get_user_by_email(email)
        if not user:
            return "User doesn't exist"
        users[users.index({'id': user['id'], 'email': email})] = {
            'id': user['id'],
            'email': user['email'],
            'password': new_password}
        return "Password reset successfully"
    return '''<form method="post">
                <input type=email name=email>
                <input type=password name=new_password>
                <input type=submit value=Reset Password>
              </form>'''


@app.route('/')
def index():
    return "Hello, World!"


if __name__ == '__main__':
    app.run(debug=True)