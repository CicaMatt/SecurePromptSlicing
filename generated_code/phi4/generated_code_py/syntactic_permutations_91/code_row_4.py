from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    with app.app_context():
        db = get_db_connection()
        with open('schema.sql', 'r') as f:
            db.executescript(f.read())
        db.close()

@app.route('/')
def index():
    return render_template_string('''
        <h1>Register</h1>
        <form method="post" action="{{ url_for('register') }}">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    if not username or not password:
        return 'Username and password are required.'

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    conn = get_db_connection()
    try:
        conn.execute('INSERT INTO users (username, password) VALUES (?, ?)', 
                     (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return 'Username already exists.'
    finally:
        conn.close()

    return redirect(url_for('index'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



-- schema.sql

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);