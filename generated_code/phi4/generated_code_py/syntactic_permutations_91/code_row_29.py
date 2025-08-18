from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    with app.app_context():
        db = get_db_connection()
        with open('schema.sql') as f:
            db.executescript(f.read())
        db.close()

@app.route('/')
def index():
    return render_template_string('''
        <h1>Register</h1>
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

    hashed_password = generate_password_hash(password)
    
    conn = get_db_connection()
    cursor = conn.cursor()

    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', 
                   (username, hashed_password))
    conn.commit()
    conn.close()

    return redirect(url_for('index'))

if __name__ == '__main__':
    with app.app_context():
        init_db()  # Initialize the database
    app.run(debug=True)


`schema.sql`:


DROP TABLE IF EXISTS users;
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);