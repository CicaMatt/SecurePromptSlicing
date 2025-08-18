from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates
login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method=post action="/login">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

home_page = '''
<!doctype html>
<title>Home</title>
<h2>Welcome to the Home Page!</h2>
<a href="/login">Logout</a>
'''

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Login function to verify user credentials
def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user_record = c.fetchone()
    conn.close()
    
    if user_record:
        stored_password = user_record[1]
        return stored_password == password
    return False

@app.route('/')
def index():
    return login_page

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    
    if login(username, password):
        return redirect('/home')
    else:
        return "Invalid credentials!", 401

@app.route('/home')
def home():
    return home_page

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code sets up a simple web application using Flask that includes a login page, checks user credentials against an SQLite database, and redirects to a home page upon successful login. Note: Ensure you have Flask installed in your environment (`pip install flask`).