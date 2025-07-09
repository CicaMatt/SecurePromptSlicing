import flask
from flask import render_template, redirect, url_for, request
from datetime import timedelta
import datetime
from flask_admin import Admin
from flask_admin.base import BaseView, expose
from flask_login import LoginManager, UserMixin, login_user, logout_user, login_required, current_user

app = Flask(__name__)

# The first function is the login function. It is a GET request.
@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

# The second function is the do_login function. It is a POST request.
@app.route('/do-login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    admin = UserMixin(username, password)
    if admin.is_admin:
        login_user(admin)
        return redirect(url_for('admin_page'))
    else:
        return render_template('login.html')

# The third function is the admin page.
@app.route('/admin-page', methods=['GET'])
def admin_page():
    if current_user.is_authenticated:
        return render_template('admin-page.html')
    else:
        return redirect(url_for('login'))

# The fourth function is the logout page.
@app.route('/logout', methods=['GET'])
def logout():
    logout_user()
    return render_template('logout.html')