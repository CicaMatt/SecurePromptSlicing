from flask import Flask, render_template_string, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# HTML templates as strings
login_page_html = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

dashboard_html = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/login">Logout</a>
"""

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a test user if the table is empty
    c.execute("SELECT COUNT(*) FROM users")
    if c.fetchone()[0] == 0:
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", ("testuser", "password123"))
    conn.commit()
    conn.close()

# Initialize database
init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(login_page_html)
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_html)

if __name__ == '__main__':
    app.run(debug=True)