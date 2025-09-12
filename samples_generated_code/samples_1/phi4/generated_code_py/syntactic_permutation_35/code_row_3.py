from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates
login_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

home_html = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Home Page</title>
  </head>
  <body>
    <h2>Welcome Home!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

# Initialize SQLite database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Login function
def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return user is not None

@app.route('/')
def index():
    return render_template_string(login_html)

@app.route('/login', methods=['GET', 'POST'])
def login_route():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if login(username, password):
            return redirect(url_for('home'))
        else:
            return redirect(url_for('index'))
    return render_template_string(login_html)

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)