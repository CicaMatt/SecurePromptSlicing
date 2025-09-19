from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes.
def init_db():
    with sqlite3.connect(':memory:') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
        # Insert a demo user for testing purposes.
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
        conn.commit()

# HTML template for login.html
LOGIN_HTML = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect(':memory:') as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
            user = cursor.fetchone()

            if user:
                return redirect('/home')
            else:
                return redirect('/login-page')

    return render_template_string(LOGIN_HTML)

@app.route('/login-page')
def login_page():
    return render_template_string(LOGIN_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)