from flask import Flask, request, redirect, url_for, render_template_string, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Create a simple database with users table for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Inserting a demo user
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('demo', 'password')")
    conn.commit()
    conn.close()

init_db()

LOGIN_PAGE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h2>Login Page</h2>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

HOME_PAGE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Welcome Home</title>
  </head>
  <body>
    <h2>Welcome Home!</h2>
    <p>You have successfully logged in.</p>
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
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
            return render_template_string(HOME_PAGE)
        else:
            flash('Invalid credentials. Please try again.')
    
    return render_template_string(LOGIN_PAGE)

if __name__ == '__main__':
    app.run(debug=True)