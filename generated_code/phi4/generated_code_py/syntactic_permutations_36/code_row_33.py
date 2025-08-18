from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates for login and home pages
LOGIN_PAGE = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
  <label>Username: <input type="text" name="username"></label><br>
  <label>Password: <input type="password" name="password"></label><br>
  <input type="submit" value="Login">
</form>
"""

HOME_PAGE = """
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<p>You have successfully logged in.</p>
<a href="/login">Logout and go back to login page</a>
"""

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a test user for demonstration purposes; in practice use hashed passwords and environment variables.
    cursor.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Function to check login credentials
def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = cursor.fetchone()
    conn.close()
    return user is not None

@app.route('/login', methods=['GET', 'POST'])
def login_view():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if login(username, password):
            return redirect('/home')
        else:
            # Optionally add an error message or log
            pass
    return render_template_string(LOGIN_PAGE)

@app.route('/home')
def home():
    return HOME_PAGE

@app.route('/')
def index():
    return redirect('/login')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code sets up a simple Flask application with an SQLite database. It includes basic routes for the login and home pages. The `init_db` function initializes the database with a test user, which is not secure for production use (passwords should be hashed and handled securely). In a real-world scenario, additional security measures like HTTPS, password hashing, and more sophisticated error handling would be necessary.