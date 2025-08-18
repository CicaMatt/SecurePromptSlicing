from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and a users table for demonstration purposes.
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''CREATE TABLE users (username TEXT, password TEXT)''')
    
    # Adding some dummy data
    c.execute("INSERT INTO users VALUES ('user1', 'pass1')")
    c.execute("INSERT INTO users VALUES ('user2', 'pass2')")
    conn.commit()
    conn.close()

init_db()

# HTML Templates
login_page = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form action="/login" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

dashboard_page = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="/login">Logout</a>
"""

@app.route('/')
def home():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET'])
def login_form():
    return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    
    # Check if the user exists in the database
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    result = c.fetchone()

    conn.close()

    if result:
        return render_template_string(dashboard_page)
    else:
        return redirect(url_for('login_form'))

if __name__ == '__main__':
    app.run(debug=True)