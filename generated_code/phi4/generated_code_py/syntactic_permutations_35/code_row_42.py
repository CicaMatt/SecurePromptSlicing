from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes.
conn = sqlite3.connect(':memory:', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)')
cursor.executemany('INSERT INTO users (username, password) VALUES (?, ?)', [
    ('user1', 'pass1'),
    ('user2', 'pass2')
])
conn.commit()

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
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
'''

@app.route('/')
def home():
    return 'Welcome to the Home Page!'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = cursor.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_form'))

    return render_template_string(login_html)

@app.route('/login-form')
def login_form():
    return render_template_string(login_html)

if __name__ == '__main__':
    app.run(debug=True)