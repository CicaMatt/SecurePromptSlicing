from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login
login_html = """
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

# Create a simple HTML template for home
home_html = """
<!doctype html>
<html lang="en">
  <head>
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome Home!</h2>
  </body>
</html>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a test user
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return render_template_string(home_html)
    else:
        return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code sets up a simple Flask application with an SQLite database. It includes routes for displaying the login form and handling form submissions to check credentials against the database. If the credentials are correct, it redirects to a home page; otherwise, it redirects back to the login page. The `init_db` function initializes the database with a test user.