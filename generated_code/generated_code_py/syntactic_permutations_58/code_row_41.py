from flask import Flask, redirect, render_template, request, session, url_for
from flask_sqlalchemy import SQLAlchemy
import hashlib

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///login_db.sqlite3'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)

@app.route('/')
def index():
    if 'username' in session:
        return f"Logged in as {session['username']} <a href='/logout'>Log Out</a>"
    else:
        return "You are not logged in <a href='/login'>Log In</a>"

@app.route('/login', methods=('GET', 'POST'))
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user and hashlib.md5(password.encode('utf-8')).hexdigest() == user.password:
            session['username'] = username
            return redirect(url_for('index'))
    else:
        return render_template('login.html')

@app.route('/logout', methods=('GET', 'POST'))
def logout():
    if request.method == 'POST':
        session.pop('username', None)
        return redirect(url_for('index'))
    else:
        return render_template('logout.html')

@app.route('/change_email', methods=('GET', 'POST'))
def change_email():
    if request.method == 'POST':
        username = session['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user and hashlib.md5(password.encode('utf-8')).hexdigest() == user.password:
            if user.email == old_email:
                user.email = new_email
                db.session.commit()
                return redirect(url_for('index'))
    else:
        return render_template('change_email.html')

if __name__ == "__main__":
    app.run()