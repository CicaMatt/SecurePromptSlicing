from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a sample database with a users table for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Adding sample user for testing
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

@login_page = '''
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
            return render_template_string(login_page)
    return render_template_string(login_page)

@app.route('/')
def home():
    return '<h1>Welcome to the Home Page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)


This code sets up a simple Flask application with SQLite as the database backend. It includes a login page and logic for handling user authentication against the database. When you run this script, it will start a web server on `localhost` which you can access by navigating to `http://127.0.0.1:5000/login`. Note that in a real-world scenario, passwords should be hashed before being stored or compared, and additional security measures should be implemented.