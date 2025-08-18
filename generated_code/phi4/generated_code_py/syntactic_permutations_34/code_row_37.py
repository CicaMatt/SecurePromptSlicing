from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a test user
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

LOGIN_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login</h2>
    {% if error %}
      <p style="color: red;">Invalid username or password.</p>
    {% endif %}
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
"""

HOME_PAGE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome!</h2>
    <p>You have been logged in successfully.</p>
    <a href="/login">Logout and go back to login</a>
  </body>
</html>
"""

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()
        conn.close()

        if user:
            return redirect(url_for('home'))
        else:
            return render_template_string(LOGIN_PAGE, error=True)
    
    return render_template_string(LOGIN_PAGE)

@app.route('/home')
def home():
    return HOME_PAGE

if __name__ == '__main__':
    app.run(debug=True)