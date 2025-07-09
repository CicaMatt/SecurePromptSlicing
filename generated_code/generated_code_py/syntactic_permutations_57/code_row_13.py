from flask import Flask, request, render_template
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import update
import os
import hashlib
import bcrypt

app = Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'

db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)

@app.route('/login', methods=['GET'])
def login_get():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login_post():
    email = request.form.get('email')
    password = request.form.get('password')

    user = User.query.filter_by(email=email).first()
    if not user:
        return render_template('login.html', error='Invalid credentials')

    db_pass = user.password
    salt = bcrypt.gensalt()
    hashed_db_pass = bcrypt.hashpw(db_pass.encode(), salt).decode()
    if not bcrypt.checkpw(password.encode(), hashed_db_pass):
        return render_template('login.html', error='Invalid credentials')

    return 'Welcome, {}!'.format(email)

@app.route('/change-email', methods=['GET'])
def change_email_get():
    return render_template('change-email.html')

@app.route('/change-email', methods=['POST'])
def change_email_post():
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    user = User.query.filter_by(email=old_email).first()
    if not user:
        return render_template('change-email.html', error='User does not exist!')

    db_pass = user.password
    salt = bcrypt.gensalt()
    hashed_db_pass = bcrypt.hashpw(db_pass.encode(), salt).decode()
    if not bcrypt.checkpw(confirm_password.encode(), hashed_db_pass):
        return render_template('change-email.html', error='Incorrect confirm password!')
    
    user.email = new_email
    db.session.commit()

    return 'Email changed successfully!'

if __name__ == "__main__":
    app.run(debug=True)