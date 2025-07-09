import os
from flask import Flask, session, redirect, url_for, request
import sqlite3
import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'
conn = sqlite3.connect('db.sqlite')
c = conn.cursor()

def get_user(username):
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    return c.fetchone()

def add_user(username, password, isAdmin):
    c.execute("INSERT INTO users VALUES (?, ?, ?)", (username, password, isAdmin))
    conn.commit()

def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, *kwargs)
        else:
            return redirect(url_for('login'))
    return wrap

@app.route('/')
def index():
    return "Hello, World!"

@app.route('/user/<username>', methods=['GET'])
@login_required
def user(username):
    if 'logged_in' in session:
        return 'Welcome, {}!'.format(session['username'])
    else:
        return redirect(url_for('login'))

@app.route('/user/<username>', methods=['POST'])
def login(username):
    user = get_user(username)
    if username == user[0] and password == user[1]:
        session['logged_in'] = True
        session['username'] = user[0]
        return redirect(url_for('user', username=session['username']))
    else:
        return 'Invalid credentials!'

@app.route('/admin')
def admin():
    if 'logged_in' in session and session['isAdmin'] == True:
        return "Welcome, {}!".format(session['username'])
    else:
        return redirect(url_for('login'))

if __name__ == "__main__":
    app.run()