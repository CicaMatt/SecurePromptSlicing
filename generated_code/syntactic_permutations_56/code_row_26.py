import hashlib
import datetime
from flask import Flask, request, session, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(64), nullable=False)

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('user'))
    else:
        return redirect(url_for('login'))

@app.route('/user', methods=['GET', 'POST'])
def user():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if not (len(old_email) >= 1 and len(new_email) >= 1):
            flash('Please enter your old and new email addresses')
        elif old_email == new_email:
            flash('Your old and new email addresses cannot be the same')
        else:
            user = User.query.filter_by(username=session['username']).first()
            if user.password != hashlib.sha256(password.encode()).hexdigest():
                flash('Incorrect password! Please try again')
            else:
                session['email'] = new_email
                flash('Your email address has been changed successfully')
    return render_template('user.html', username=session['username'], email=session['email'])

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if not user:
            flash('Incorrect username or password! Please try again')
        elif hashlib.sha256(password.encode()).hexdigest() != user.password:
            flash('Incorrect username or password! Please try again')
        else:
            session['username'] = user.username
            session['email'] = user.email
            return redirect(url_for('user'))
    return render_template('login.html')

@app.route('/logout', methods=['GET'])
def logout():
    if 'username' in session:
        flash('You have been logged out')
        session.pop('username', None)
        return redirect(url_for('index'))
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run()