from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

HTML_LOGIN_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

HTML_HOME_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
  </body>
</html>
"""

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    return render_template_string(HTML_LOGIN_PAGE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
        conn.close()

        if user:
            return redirect('/home')
        else:
            return redirect('/')
    return render_template_string(HTML_LOGIN_PAGE)

@app.route('/home')
def home_page():
    return render_template_string(HTML_HOME_PAGE)

# Create a database and table for demonstration purposes
def init_db():
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)')
    # Add test user
    conn.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
    conn.commit()
    conn.close()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


Make sure you have Flask installed in your environment. You can install it using `pip install flask`. This script creates a simple web application with login functionality, using SQLite as the database backend for storing user credentials.