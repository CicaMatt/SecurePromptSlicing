from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database with a users table
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a test user if the table is empty
    c.execute("SELECT COUNT(*) FROM users")
    if c.fetchone()[0] == 0:
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

# Initialize database
init_db()

HTML_LOGIN = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Login</title>
</head>
<body>
  <h2>Login</h2>
  <form method="post" action="{{ url_for('login') }}">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
  </form>
  {% if error %}
  <p style="color:red;">Invalid username or password. Please try again.</p>
  {% endif %}
</body>
</html>
"""

HTML_HOME = """
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Home</title>
</head>
<body>
  <h2>Welcome to the Home Page!</h2>
  <a href="{{ url_for('login') }}">Logout</a>
</body>
</html>
"""

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
            return render_template_string(HTML_LOGIN, error=True)

    return render_template_string(HTML_LOGIN, error=False)

@app.route('/home')
def home():
    return HTML_HOME

if __name__ == '__main__':
    app.run(debug=True)