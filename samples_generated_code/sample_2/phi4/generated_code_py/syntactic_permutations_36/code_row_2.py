from flask import Flask, request, redirect, url_for, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple login form template
LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

# Home page template
HOME_PAGE = '''
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
'''

# Initialize SQLite database and create users table if not exists
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL
        )
    ''')
    # Add a default user for testing
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

@app.route('/')
def home():
    return HOME_PAGE

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if check_login(username, password):
            return redirect(url_for('home'))
        else:
            return render_template_string(LOGIN_FORM + "<p>Invalid username or password</p>")
    
    return render_template_string(LOGIN_FORM)

def check_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = cursor.fetchone()
    conn.close()

    if user:
        return True
    return False

if __name__ == '__main__':
    init_db()
    app.run(debug=True)