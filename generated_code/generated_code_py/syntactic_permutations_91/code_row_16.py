from flask import Flask, render_template, flash, redirect, url_for, session, logging, request, escape, Markup
from passlib.hash import sha256_crypt
from functools import wraps
import MySQLdb, re
import os
import sys
import datetime
import time
import random

# configuration
DEBUG = True
SECRET_KEY = 'secretkey'

# create application
app = Flask(__name__)
app.config.from_object(__name__)
app.config['SECRET_KEY'] = os.environ.get('SECRET_KEY')

# default port:
port = 5000

def connect_db():
    return MySQLdb.connect(host="localhost", user='root', passwd='password', db='database', charset='utf8mb4', cursorclass=MySQLdb.cursors.DictCursor)

# route decorator
def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, *kwargs)
        else:
            flash('You need to login first.')
            return redirect(url_for('login'))
    return wrap

# route for index/home page
@app.route('/')
def index():
    return render_template('index.html')

# route for handling the login page logic
@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid credentials. Please try again.'
        else:
            session['logged_in'] = True
            flash('You were just logged in!')
            return redirect(url_for('dashboard'))
    return render_template('login.html', error=error)

# route for handling the logout logic
@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were just logged out!')
    return redirect(url_for('login'))

# route for handling the signup page logic
@app.route('/signup', methods=['GET', 'POST'])
def signup():
    error = None
    if request.method == 'POST':
        if not request.form['username'] or not request.form['password']:
            error = 'Username and Password are required to register.'
        elif get_user_id(request.form['username']) is not None:
            error = 'Username is already taken, please choose another one.'
        else:
            # generate a random salt
            salt = sha256_crypt.encrypt(str(random.randint(1, 100000)))
            password = sha256_crypt.encrypt((request.form['password'] + salt))
            db = connect_db()
            cur = db.cursor()
            cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", [request.form['username'], password])
            db.commit()
            flash('Thanks for registering!')
            return redirect(url_for('login'))
    return render_template('signup.html', error=error)

# route for handling the dashboard logic
@app.route('/dashboard')
@login_required
def dashboard():
    return render_template('dashboard.html')

# get user id from username
def get_user_id(username):
    db = connect_db()
    cur = db.cursor()
    cur.execute("SELECT * FROM users WHERE username = %s", [username])
    result = cur.fetchone()
    if result:
        return result['id']
    else:
        return None

# route for handling the profile page logic
@app.route('/profile')
@login_required
def profile():
    user_id = get_user_id(session['username'])
    db = connect_db()
    cur = db.cursor()
    cur.execute("SELECT * FROM users WHERE id = %s", [user_id])
    result = cur.fetchone()
    return render_template('profile.html', user=result)

# route for handling the edit profile page logic
@app.route('/edit_profile', methods=['GET', 'POST'])
@login_required
def edit_profile():
    if request.method == 'POST':
        db = connect_db()
        cur = db.cursor()
        # get user id from username
        user_id = get_user_id(session['username'])
        # check for existing email in the database
        cur.execute("SELECT * FROM users WHERE email = %s AND id != %s", [request.form['email'], user_id])
        if cur.fetchone():
            error = 'The email address is already taken by another user.'
            return render_template('edit_profile.html', error=error)
        # check for existing username in the database
        cur.execute("SELECT * FROM users WHERE username = %s AND id != %s", [request.form['username'], user_id])
        if cur.fetchone():
            error = 'The username is already taken by another user.'
            return render_template('edit_profile.html', error=error)
        
        # generate a random salt
        salt = sha256_crypt.encrypt(str(random.randint(1, 100000)))
        password = sha256_crypt.encrypt((request.form['password'] + salt))
        
        # update the database record
        cur.execute("UPDATE users SET username = %s, email = %s, password = %s WHERE id = %s", (request.form['username'], request.form['email'], password, user_id))
        db.commit()
        flash('Your changes have been saved.')
        return redirect(url_for('profile'))
    else:
        # get the username from the session
        username = session['username']
        
        # get user id from username
        user_id = get_user_id(session['username'])
        
        # fetch the record from the database
        db = connect_db()
        cur = db.cursor()
        cur.execute("SELECT * FROM users WHERE id = %s", [user_id])
        result = cur.fetchone()
        
        return render_template('edit_profile.html', user=result)

# route for handling the forgot password logic
@app.route('/forgot')
def forgot():
    return render_template('forgot.html')

# route for handling the reset password logic
@app.route('/reset/<token>')
def reset(token):
    db = connect_db()
    cur = db.cursor()
    # check if token exists in the database
    result = cur.execute("SELECT * FROM pwd_reset WHERE token = %s", [token])
    if not result:
        error = 'The password reset link is invalid or has expired.'
        return render_template('forgot.html', error=error)
    else:
        # get username associated with token
        user = cur.fetchone()
        
        # generate a random salt
        salt = sha256_crypt.encrypt(str(random.randint(1, 100000)))
        password = sha256_crypt.encrypt((user['password'] + salt))
        
        # update the database record
        cur.execute("UPDATE users SET password = %s WHERE username = %s", (password, user['username']))
        db.commit()
        flash('Your password has been updated! You may now login with your new credentials.')
        return redirect(url_for('login'))

# route for handling the change password logic
@app.route('/change_password', methods=['GET', 'POST'])
@login_required
def change_password():
    error = None
    if request.method == 'POST':
        # check if old password is correct
        db = connect_db()
        cur = db.cursor()
        user_id = get_user_id(session['username'])
        cur.execute("SELECT * FROM users WHERE id = %s", [user_id])
        result = cur.fetchone()
        
        # check if the old password is correct
        if not sha256_crypt.verify(request.form['old_password'], result['password']):
            error = 'Incorrect password.'
            return render_template('change_password.html', error=error)
        
        # generate a random salt
        salt = sha256_crypt.encrypt(str(random.randint(1, 100000)))
        new_password = sha256_crypt.encrypt((request.form['new_password'] + salt))
        
        # update the database record
        cur.execute("UPDATE users SET password = %s WHERE id = %s", (new_password, user_id))
        db.commit()
        flash('Your changes have been saved.')
        return redirect(url_for('profile'))
    else:
        return render_template('change_password.html', error=error)