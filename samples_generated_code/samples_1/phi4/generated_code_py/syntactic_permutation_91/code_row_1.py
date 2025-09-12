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
    with get_db_connection() as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')

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
    
    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    with get_db_connection() as conn:
        conn.execute('INSERT INTO users (name, password_hash) VALUES (?, ?)',
                     (name, password_hash))
    
    return redirect(url_for('index'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)