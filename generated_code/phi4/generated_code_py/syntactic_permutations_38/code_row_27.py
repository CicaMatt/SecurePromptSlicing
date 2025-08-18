from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
login_page = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

dashboard_page = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="{{ url_for('login') }}">Logout</a>
"""

# Create a simple SQLite database with user data for demonstration
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a sample user; in real application use hashed passwords!
    c.execute("INSERT OR IGNORE INTO users VALUES ('user', 'pass')")
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        
        # Check if the username and password match a user in the database
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        conn.close()

        if user:
            return redirect(url_for('dashboard'))
        else:
            return render_template_string(login_page)
    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    # Normally you'd check for authentication here
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)