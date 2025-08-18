from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize database connection
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    html = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
    conn.close()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login_page'))

@app.route('/dashboard')
def dashboard():
    html = '''
    <h1>Welcome to the Dashboard</h1>
    <a href="/">Logout</a>
    '''
    return render_template_string(html)

# Create database and table
def init_db():
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)')
    # Add a test user for demonstration purposes
    conn.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
    conn.commit()
    conn.close()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code sets up a simple Flask application with SQLite as the database. It includes routes for logging in and displaying the dashboard. The `/` route serves the login page, while the `/login` route handles authentication against the `users` table in the SQLite database. If the credentials match, it redirects to the `/dashboard`; otherwise, it returns to the login page.

Please note that storing passwords as plain text is insecure and should not be used in production code. Passwords should be hashed using a library like `bcrypt`. This example is for educational purposes only.