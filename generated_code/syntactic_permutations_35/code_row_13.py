import os
from flask_login import UserMixin, LoginManager, current_user
from flask import Flask, render_template, request, redirect, url_for
from werkzeug.security import generate_password_hash, check_password_hash
import sqlite3

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your secret key'
login_manager = LoginManager()
login_manager.init_app(app)
conn = sqlite3.connect('database.db')
cursor = conn.cursor()

class User(UserMixin):
    def __init__(self, username, password):
        self.id = username
        self.password = password

@login_manager.user_loader
def user_loader(username):
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    row = cursor.fetchone()
    if row:
        return User(row[0], row[1])

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/process-login', methods=['POST'])
def process_login():
    username = request.form['username']
    password = request.form['password']
    cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    row = cursor.fetchone()
    if row:
        user = User(row[0], row[1])
        login_user(user)
        return redirect(url_for('home'))
    else:
        return 'Invalid username or password'

@app.route('/')
def home():
    return '<h1>Home page</h1>'

if __name__ == "__main__":
    app.run()