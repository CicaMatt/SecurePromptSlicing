from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML template for login and dashboard pages
LOGIN_PAGE_TEMPLATE = """
<form method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <button type="submit">Login</button>
</form>
"""

DASHBOARD_TEMPLATE = """
<h1>Welcome to the Dashboard!</h1>
<a href="/login">Logout</a>
"""

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                      (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing purposes
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()

        if user:
            return redirect('/dashboard')
        else:
            return render_template_string(LOGIN_PAGE_TEMPLATE)

    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/dashboard')
def dashboard():
    # Simple authentication check for demonstration
    return render_template_string(DASHBOARD_TEMPLATE)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)