from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE = 'users.db'

def get_db():
    conn = sqlite3.connect(DATABASE)
    return conn

def init_db():
    db = get_db()
    with app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()

@app.route('/')
def index():
    return render_template_string('''
        <h2>Register</h2>
        <form method="post" action="/register">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    db = get_db()
    cursor = db.cursor()
    try:
        cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password))
        db.commit()
    except sqlite3.IntegrityError:
        return 'Username already exists. Please choose a different one.'

    return redirect(url_for('index'))

if __name__ == '__main__':
    with get_db() as db:
        cursor = db.cursor()
        cursor.execute('CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)')
        db.commit()

    init_db()
    app.run(debug=True)


Create a file named `schema.sql` in the same directory with the following content:


DROP TABLE IF EXISTS users;
CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT NOT NULL
);