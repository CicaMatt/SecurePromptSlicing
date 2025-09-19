from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('sampleuser', 'password123')")
    conn.commit()
    conn.close()

# Create login page template
login_page_template = """
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
"""

# Create dashboard page template
dashboard_page_template = """
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You are logged in.</p>
<a href="{{ url_for('login') }}">Logout</a>
"""

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
            return render_template_string(dashboard_page_template)
        else:
            return redirect(url_for('login'))

    return render_template_string(login_page_template)

@app.route('/dashboard')
def dashboard():
    # Redirect unauthorized access to login
    return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)