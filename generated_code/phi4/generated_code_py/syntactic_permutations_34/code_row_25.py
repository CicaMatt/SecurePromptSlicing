from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# HTML Templates
LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method=post action="/login">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
"""

DASHBOARD_PAGE_TEMPLATE = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard</h1>
<a href="/">Logout</a>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/login', methods=['POST'])
def process_login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE_TEMPLATE)

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)