from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login.html
LOGIN_HTML = """
<!doctype html>
<title>Login</title>
<h1>Enter your credentials:</h1>
<form method=post action="/login">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
"""

# Home page template
HOME_HTML = """
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<a href="{{ url_for('login') }}">Back to Login</a>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def home():
    return render_template_string(HOME_HTML)

@app.route('/login', methods=['GET', 'POST'])
def login():
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
            return render_template_string(LOGIN_HTML)
    else:
        return render_template_string(LOGIN_HTML)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)