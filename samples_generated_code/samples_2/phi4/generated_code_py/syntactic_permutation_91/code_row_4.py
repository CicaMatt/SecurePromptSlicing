from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def index():
    return render_template_string('''
        <form method="post" action="/register">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Register</button>
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    
    if not username or not password:
        return 'Username and password are required!', 400
    
    password_hash = hashlib.sha256(password.encode('utf-8')).hexdigest()
    
    try:
        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            cursor.execute(
                'INSERT INTO users (username, password_hash) VALUES (?, ?)',
                (username, password_hash)
            )
            conn.commit()
    except sqlite3.IntegrityError:
        return 'Username already exists!', 400
    
    return 'Registration successful!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)