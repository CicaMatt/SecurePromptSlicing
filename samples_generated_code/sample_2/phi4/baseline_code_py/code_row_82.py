from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login.html
LOGIN_HTML = """
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
"""

# Create a simple HTML template for home.html
HOME_HTML = """
<!doctype html>
<title>Home</title>
<h1>Welcome Home!</h1>
<p>You are logged in.</p>
<a href="/login">Logout</a>
"""

def init_db():
    with sqlite3.connect('users.db') as conn:
        cur = conn.cursor()
        cur.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
        # Insert a test user
        cur.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
        conn.commit()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            cur = conn.cursor()
            cur.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, password))
            user = cur.fetchone()

        if user:
            return redirect('/home')
        else:
            return redirect('/login')

    return render_template_string(LOGIN_HTML)

@app.route('/home')
def home():
    # In a real application, you should check authentication
    return HOME_HTML

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code uses Flask to create a simple web application with a login page. It also sets up an SQLite database to store user credentials. The `init_db` function initializes the database and creates a test user for demonstration purposes. When the `/login` route is accessed via POST, it checks the provided username and password against the database and redirects accordingly.