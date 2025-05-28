import os
from flask import Flask, redirect, url_for, request, render_template
from werkzeug.security import generate_password_hash, check_password_hash
from sqlalchemy import create_engine, text

app = Flask(__name__)

engine = create_engine(os.environ['DATABASE_URL'], echo=True)
connection = engine.connect()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['POST'])
def register():
    username = request.form.get('username')
    password = request.form.get('password')
    error = None

    if not username:
        error = 'Username is required.'
    elif not password:
        error = 'Password is required.'
    elif connection.execute(text("SELECT * FROM users WHERE username= :username"), {'username': username}).fetchone() is not None:
        error = f"User {username} is already registered."

    if error is None:
        hashed_password = generate_password_hash(password)
        connection.execute(text("INSERT INTO users (username, password) VALUES (:username, :password)"), {'username': username, 'password': hashed_password})
        return redirect(url_for('login'))
    else:
        return render_template('register.html', error=error)

@app.route('/login')
def login():
    return render_template('login.html')

if __name__ == "__main__":
    app.run()