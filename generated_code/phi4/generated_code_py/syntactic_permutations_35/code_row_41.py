from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

# HTML templates as strings for demonstration purposes
LOGIN_HTML = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <button type="submit">Login</button>
</form>
'''

HOME_HTML = '''
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page!</h1>
<p>This is the home page after a successful login.</p>
<a href="/login">Logout and go back to login</a>
'''

# Initialize database
def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    # Insert a test user, remove or comment out in production!
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect(DATABASE)
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    return render_template_string(LOGIN_HTML)

@app.route('/')
def home():
    return render_template_string(HOME_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)