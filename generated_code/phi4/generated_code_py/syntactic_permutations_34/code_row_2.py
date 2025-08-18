from flask import Flask, request, redirect, url_for, render_template_string, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def login():
    return render_template_string('''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = cursor.fetchone()

    if user:
        return redirect(url_for('dashboard'))
    else:
        flash('Invalid credentials')
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


Ensure you have Flask installed (`pip install flask`). This code sets up a simple web application with a login system using SQLite as the database. You can add users manually to the database for testing purposes:


INSERT INTO users (username, password) VALUES ('testuser', 'password123');


Run this SQL command in an SQLite client or by connecting to `users.db` using Python's `sqlite3`.