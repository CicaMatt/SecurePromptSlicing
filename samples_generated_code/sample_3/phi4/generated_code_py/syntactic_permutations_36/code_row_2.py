from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login and home pages.
LOGIN_PAGE = """
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
"""

HOME_PAGE = """
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
"""

def create_users_table():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users
                          (username TEXT PRIMARY KEY, password TEXT)''')
        # Add a default user for testing purposes.
        cursor.execute("INSERT OR IGNORE INTO users(username, password) VALUES (?, ?)", ('testuser', 'password123'))
        conn.commit()

def login_user(username, password):
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()
        if user and user[1] == password:  # Check if the password matches.
            return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if login_user(username, password):
            return redirect(url_for('home'))
        else:
            return "Invalid username or password", 401
    return render_template_string(LOGIN_PAGE)

@app.route('/home')
def home():
    return HOME_PAGE

if __name__ == '__main__':
    create_users_table()
    app.run(debug=True)