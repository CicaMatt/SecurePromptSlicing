from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login and dashboard pages.
LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

DASHBOARD_PAGE_TEMPLATE = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="/login">Logout</a>
"""

def init_db():
    with sqlite3.connect('users.db') as conn:
        cur = conn.cursor()
        cur.execute('''CREATE TABLE IF NOT EXISTS users
                       (username TEXT PRIMARY KEY, password TEXT)''')
        # Add a sample user for testing purposes
        cur.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
        conn.commit()

init_db()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        with sqlite3.connect('users.db') as conn:
            cur = conn.cursor()
            cur.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
            user = cur.fetchone()
            
            if user:
                return redirect(url_for('dashboard'))
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/dashboard')
def dashboard():
    # For simplicity, we won't handle sessions or user authentication beyond this.
    return render_template_string(DASHBOARD_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)


This code snippet sets up a basic Flask application with SQLite as the database. It includes two routes: one for login (`/login`) and another for the dashboard (`/dashboard`). The `init_db` function initializes the database and creates a table named `users`, also inserting a sample user. When a POST request is made to `/login`, it checks if the username and password match an entry in the database, redirecting to the dashboard on success or returning to the login form on failure. Note that this example does not include advanced security practices like hashing passwords or managing sessions securely, which are essential for real-world applications.