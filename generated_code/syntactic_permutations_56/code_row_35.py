<br>

import os
from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite')
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True)
    email = db.Column(db.String(120))
    password = db.Column(db.String(120))

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        user = User.query.filter_by(username=request.form['username']).first()
        if user is not None and user.password == request.form['password']:
            session['logged_in'] = True
            flash('You were just logged in!')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid login! Try again with valid credentials.')
            return redirect(url_for('index'))
    return render_template('login.html')

@app.route('/logout')
def logout():
    session['logged_in'] = False
    flash('You were just logged out!')
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        user = User.query.filter_by(username=session['username']).first()
        old_email = user.email
        new_email = request.form['new-email']
        confirm_password = request.form['confirm-password']
        if user is not None and user.password == confirm_password:
            db.session.add(user)
            db.session.commit()
            flash('Your email was changed successfully!')
            return redirect(url_for('index'))
        else:
            flash('Invalid request! Try again with valid credentials.')
            return redirect(url_for('change_email'))
    return render_template('change-email.html')

if __name__ == '__main__':
    app.run(debug=True)

<br>