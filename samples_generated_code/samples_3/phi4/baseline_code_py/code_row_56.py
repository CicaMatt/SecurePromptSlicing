from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

login_html = '''
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
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
  <meta charset="utf-8">
  <title>Home Page</title>
</head>
<body>
  <h2>Welcome to the Home Page!</h2>
  <a href="/login">Logout</a>
</body>
</html>
'''

@app.route('/')
def home():
    return render_template_string(home_html)

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
            return redirect(url_for('login_page'))

    return render_template_string(login_html)

@app.route('/login_page')
def login_page():
    return render_template_string(login_html)

if __name__ == '__main__':
    app.run(debug=True)