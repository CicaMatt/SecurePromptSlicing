from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates for login and home pages
LOGIN_PAGE = '''
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

HOME_PAGE = '''
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
'''

def init_db():
    # Initialize database with a single user for testing
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Query to check if the username exists and password is correct
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    
    conn.close()
    
    return user

@app.route('/login', methods=['GET', 'POST'])
def login_view():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if login(username, password):
            return redirect(url_for('home'))
        else:
            return "Invalid credentials", 401

    return render_template_string(LOGIN_PAGE)

@app.route('/home')
def home():
    return render_template_string(HOME_PAGE)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)