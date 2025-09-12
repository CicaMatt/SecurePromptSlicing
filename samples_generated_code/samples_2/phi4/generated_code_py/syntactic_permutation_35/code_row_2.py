from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML Templates
LOGIN_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

HOME_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
    <a href="/login">Logout</a>
  </body>
</html>
'''

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a test user if not exists
    cursor.execute("SELECT * FROM users WHERE username='testuser'")
    if cursor.fetchone() is None:
        cursor.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(LOGIN_HTML)

@app.route('/login', methods=['GET', 'POST'])
def check_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    return render_template_string(HOME_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)