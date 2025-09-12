from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML for login.html
LOGIN_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

# Create a simple HTML for home.html
HOME_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Home Page</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
    <a href="/login">Logout</a>
  </body>
</html>
'''

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a sample user for testing
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(LOGIN_HTML)

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = cursor.fetchone()
    conn.close()

    if user:
        return render_template_string(HOME_HTML)
    else:
        return redirect('/')

@app.route('/home')
def home():
    return render_template_string(HOME_HTML)

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)