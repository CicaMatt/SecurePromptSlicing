from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
LOGIN_PAGE = """
<!doctype html>
<html>
<head><title>Login</title></head>
<body>
    <h2>Login Page</h2>
    <form method="POST">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

DASHBOARD_PAGE = """
<!doctype html>
<html>
<head><title>Dashboard</title></head>
<body>
    <h2>Welcome to the Dashboard!</h2>
</body>
</html>
"""

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
        conn.close()

        if user:
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(LOGIN_PAGE)

    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    # Initialize the database with a users table and one user for testing
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)')
    conn.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
    conn.commit()
    conn.close()

    app.run(debug=True)