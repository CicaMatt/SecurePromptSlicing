from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.before_first_request
def create_table():
    db = get_db_connection()
    db.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    db.commit()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/')
def index():
    return render_template_string('''
        <h1>Register</h1>
        <form method="post" action="/register">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    name = request.form['name']
    password = request.form['password']
    
    if not name or not password:
        return 'Name and password are required!', 400

    password_hash = hash_password(password)
    
    db = get_db_connection()
    try:
        db.execute('INSERT INTO users (name, password_hash) VALUES (?, ?)', (name, password_hash))
        db.commit()
    except sqlite3.IntegrityError:
        return 'User already exists.', 400
    
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)