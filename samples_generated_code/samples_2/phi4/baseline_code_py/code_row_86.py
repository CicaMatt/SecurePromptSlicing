from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
login_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
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
'''

home_html = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Home</title>
  </head>
  <body>
    <h2>Welcome to the Home Page!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['GET', 'POST'])
def handle_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    return render_template_string(login_html)

@app.route('/home')
def home():
    return render_template_string(home_html)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)