import os
from flask import Flask, flash, redirect, render_template, request, session, abort
from functools import wraps
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# Set up the database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

# Decorator to check if user logged in
def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('Unauthorized, Please login', 'danger')
            return redirect('/login')
    return wrap

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        password = request.form['password']
        user = User(username=username, email=email)
        db.session.add(user)
        db.session.commit()
        flash('Thanks for registering!')
    return render_template('register.html')

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user is not None:
            session['logged_in'] = True
            return redirect('/')
    return render_template('login.html')

@app.route('/user/<string:username>')
def user(username):
    user = User.query.filter_by(username=username).first()
    if user is not None:
        return render_template('profile.html', username=username)
    else:
        abort(404)

@app.route('/logout')
def logout():
    session['logged_in'] = False
    flash('You have been logged out!')
    return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)