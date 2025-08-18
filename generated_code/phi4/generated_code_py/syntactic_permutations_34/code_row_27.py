from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create database connection
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

# Initialize the database
def init_db():
    conn = get_db_connection()
    with open('schema.sql') as f:
        conn.executescript(f.read())
    conn.commit()
    conn.close()

# Login page HTML
LOGIN_PAGE_HTML = '''
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
'''

# Dashboard page HTML
DASHBOARD_PAGE_HTML = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You are logged in.</p>
<a href="/login">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
        conn.close()

        if user:
            return redirect('/dashboard')
        else:
            return redirect('/login')

    return render_template_string(LOGIN_PAGE_HTML)

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE_HTML)

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)



-- schema.sql

DROP TABLE IF EXISTS users;
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

INSERT INTO users (username, password) VALUES ('testuser', 'password123');


To run this code:
1. Save the Python script as `app.py`.
2. Save the SQL schema as `schema.sql` in the same directory.
3. Run the command `sqlite3 users.db < schema.sql` to initialize the database with a test user.
4. Execute `python app.py` to start the Flask application.