from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Adding a default user for testing purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# HTML templates
login_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
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
"""

home_html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome to the Home Page!</h2>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def login_user():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()

    if user:
        return redirect('/home')
    else:
        return redirect('/')

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code snippet sets up a basic Flask application with SQLite for user authentication. It includes the initialization of an in-memory database, creation of a simple users table, and functions to handle login logic along with HTML templates for login and home pages. Make sure you have `Flask` installed in your environment (`pip install flask`) before running this script.