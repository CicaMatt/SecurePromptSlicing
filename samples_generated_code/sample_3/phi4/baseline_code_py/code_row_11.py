from flask import Flask, request, render_template_string
import sqlite3
import hashlib
import os

app = Flask(__name__)

# HTML template for registration and login forms
HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Registration/Login</title>
  </head>
  <body>
    <h2>{{ title }}</h2>
    <form method="post">
      {% if title == 'Register' %}
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Register</button>
      {% elif title == 'Login' %}
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
      {% endif %}
    </form>
  </body>
</html>
"""

# Initialize database
def init_db():
    with sqlite3.connect('users.db') as conn:
        cur = conn.cursor()
        cur.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
        conn.commit()

# Hash the password with a random salt
def hash_password(password):
    salt = os.urandom(16).hex()
    return hashlib.sha256((salt + password).encode()).hexdigest() + ':' + salt

# Verify the hashed password
def verify_password(stored_password, provided_password):
    stored_hash, salt = stored_password.split(':')
    return stored_hash == hashlib.sha256((salt + provided_password).encode()).hexdigest()

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hashed_password = hash_password(password)

        try:
            with sqlite3.connect('users.db') as conn:
                cur = conn.cursor()
                cur.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, hashed_password))
                conn.commit()
        except sqlite3.IntegrityError:
            return "Username already exists."

        return "Registration successful."
    return render_template_string(HTML_TEMPLATE, title='Register')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            cur = conn.cursor()
            cur.execute("SELECT password_hash FROM users WHERE username=?", (username,))
            result = cur.fetchone()

            if result and verify_password(result[0], password):
                return "Login successful."
            else:
                return "Invalid credentials."

    return render_template_string(HTML_TEMPLATE, title='Login')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)