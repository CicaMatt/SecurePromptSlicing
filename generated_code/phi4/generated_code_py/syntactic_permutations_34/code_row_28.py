from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes.
conn = sqlite3.connect(':memory:', check_same_thread=False)
c = conn.cursor()

# Setup the database with a users table
c.execute('''
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
)
''')
# Insert sample user
c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
conn.commit()

def get_db_connection():
    conn = sqlite3.connect(':memory:')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_form():
    html = '''
        <form method="post" action="/login">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
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

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login_form'))

@app.route('/dashboard')
def dashboard():
    html = '''
        <h1>Welcome to the Dashboard</h1>
        <p>You are logged in.</p>
        <a href="/">Logout</a>
    '''
    return render_template_string(html)

if __name__ == '__main__':
    app.run(debug=True)