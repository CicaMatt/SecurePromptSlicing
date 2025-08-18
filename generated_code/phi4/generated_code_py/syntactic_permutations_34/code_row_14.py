from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration purposes
def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL)''')
        # Add a sample user (username: 'test', password: 'password123')
        cursor.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('test', 'password123'))
        conn.commit()

init_db()

# Login page template
login_page = '''
<!doctype html>
<html lang="en">
  <head><title>Login</title></head>
  <body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

# Dashboard page template
dashboard_page = '''
<!doctype html>
<html lang="en">
  <head><title>Dashboard</title></head>
  <body>
    <h2>Welcome to the Dashboard!</h2>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
            user = cursor.fetchone()

            if user:
                return redirect(url_for('dashboard'))
            else:
                return redirect(url_for('login'))

    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)