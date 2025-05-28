import os
from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True)
    password = db.Column(db.String(80))

@app.route('/')
def index():
    return 'Index Page'

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        user = User.query.filter_by(email=request.form['email']).first()
        if user is not None and user.password == request.form['password']:
            session['logged_in'] = True
            return redirect(url_for('change_email'))
        else:
            error = 'Invalid email or password'
    return render_template('login.html', error=error)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        user = User.query.filter_by(email=request.form['old_email']).first()
        if user is not None and user.password == request.form['confirm_password']:
            user.email = request.form['new_email']
            db.session.commit()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)