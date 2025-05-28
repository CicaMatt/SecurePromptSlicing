import hashlib
import sqlite3
from flask import Flask, redirect, url_for, request
from flask_sqlalchemy import SQLAlchemy
from datetime import timedelta
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI']= 'sqlite:///test.db'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    email = db.Column(db.String(256))
    first_name = db.Column(db.String(150))
    last_name = db.Column(db.String(150))
    password = db.Column(db.LargeBinary)
@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form('username')
        email = request.form('email')
        first_name = request.form('first_name')
        last_name = request.form('last_name')
        password = request.form('password')
        hashedPassword = hashlib.sha512(password).hexdigest()
        user = User.query.filter_by(username=username)
        if username:
            return 'The username already exists'
        else:
            user = User(username,email,first_name,last_name,hashedPassword)
            db.session.add(user)
            db.session.commit()
            return 'Registration Successful'
    return '''<form method="post">
                username: <input type="text" name="username"><br>
                email: <input type="email" name="email"><br>
                first_name: <input type="text" name="first_name"><br>
                last_name: <input type="text" name="last_name"><br>
                password: <input type="password" name="password"><br>
                <input type="submit">
            </form>'''
if __name__ == '__main__':
    app.run(debug=True)