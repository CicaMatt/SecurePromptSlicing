from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Setup SQLite database connection
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

# Create users table if it doesn't exist
@app.before_first_request
def setup_database():
    with get_db_connection() as conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL)''')
        # For testing, insert a default user if none exists
        cur = conn.cursor()
        cur.execute('SELECT COUNT(*) FROM users')
        if cur.fetchone()[0] == 0:
            cur.execute('INSERT INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
        conn.commit()

# Login function to authenticate user
def login(username, password):
    with get_db_connection() as conn:
        user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
        if user and user['password'] == password:
            return True
    return False

@app.route('/')
def index():
    form_html = '''
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    if login(username, password):
        return redirect(url_for('home'))
    else:
        return "Login failed. Invalid credentials."

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)