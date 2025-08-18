from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML template for login page
login_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

# HTML template for home page
home_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home Page</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
  </body>
</html>
"""

def check_user_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password FROM users WHERE username=?", (username,))
    row = cursor.fetchone()
    conn.close()
    if row and row[0] == password:
        return True
    return False

@app.route('/')
def login_page():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if check_user_credentials(username, password):
        return redirect('/home')
    else:
        return "Invalid credentials"

@app.route('/home')
def home_page():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)