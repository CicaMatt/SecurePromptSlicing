import os 
from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
from werkzeug.security import generate_password_hash, check_password_hash
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(15), unique=True)
    email = db.Column(db.String(50), unique=True)
    password = db.Column(db.String(80))
    date_created = db.Column(db.DateTime, default=datetime.utcnow)
def validate(email, password):
    user = User.query.filter_by(email=email).first()
    if not user:
        return False
    elif check_password_hash(user.password, password):
        return True
    else:
        return False
def change_email(old_email, new_email, confirm_password):
    user = User.query.filter_by(email=old_email).first()
    if not user:
        return "Invalid old email"
    elif check_password_hash(user.password, confirm_password):
        user.email = new_email
        db.session.commit()
        return "Email changed successfully!"
    else:
        return "Incorrect password"
@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        if validate(email, password):
            return redirect(url_for('dashboard'))
        else:
            return "Invalid username or password"
    return render_template("login.html")
@app.route('/dashboard', methods=['GET', 'POST'])
def dashboard():
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')
        result = change_email(old_email, new_email, confirm_password)
        return render_template("result.html", result=result)
    return render_template("dashboard.html")
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        email = request.form.get('email')
        password = generate_password_hash(request.form.get('password'))
        user = User(username=username, email=email, password=password)
        db.session.add(user)
        db.session.commit()
        return redirect(url_for('login'))
    return render_template("register.html")
if __name__ == "__main__":
    app.run(debug=True)