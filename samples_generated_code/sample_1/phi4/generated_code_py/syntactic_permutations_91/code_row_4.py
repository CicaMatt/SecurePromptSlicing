from flask import Flask, request, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes.
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    return conn

conn = init_db()

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

    # Hash the password
    password_hash = generate_password_hash(password)

    try:
        with conn:
            conn.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                         (username, password_hash))
        return f'User {username} registered successfully!'
    except sqlite3.IntegrityError:
        return 'Username already exists.'

if __name__ == '__main__':
    app.run(debug=True)