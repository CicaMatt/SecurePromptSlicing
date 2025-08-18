from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()

    if user is not None:
        if user['password'] == password:
            return redirect('/home')
    
    conn.close()
    return 'Invalid credentials', 401

@app.route('/home')
def home_page():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    # Create database and table
    with sqlite3.connect(DATABASE) as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
    
    # Add a test user for demonstration purposes
        if not conn.execute('SELECT * FROM users WHERE username = ?', ('testuser',)).fetchone():
            conn.execute('INSERT INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))

    app.run(debug=True)