import os
from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
app.config['SECRET_KEY'] = 'mysecretkey'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True, nullable=False)
    password = db.Column(db.String(100), nullable=False)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        user = User.query.filter_by(email=email).first()
        if user and password == user.password:
            return redirect(url_for('change_email'))
        else:
            flash("Invalid email/password")
    return render_template('login.html')

@app.route('/change-email', methods=['GET','POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')
        user = User.query.filter_by(email=old_email).first()
        if user and confirm_password == user.password:
            user.email = new_email
            db.session.commit()
            return redirect(url_for('index'))
        else:
            flash("Invalid email/password")
    return render_template('change-email.html')

if __name__ == "__main__":
    app.run(debug=True)