from flask import Flask, render_template_string, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# HTML Templates
login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
'''

dashboard_html = '''
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<p>{{ message }}</p>
<a href="{{ url_for('login') }}">Logout</a>
'''

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return user is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return redirect(url_for('dashboard'))
    # Render the login page
    return render_template_string(login_page_html)

@app.route('/dashboard')
def dashboard():
    message = "You are logged in!"
    return render_template_string(dashboard_html, message=message)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


Make sure you have Flask installed. You can install it using `pip install flask`. This script sets up a simple web application with login and dashboard functionality, using SQLite as the database to store user credentials.