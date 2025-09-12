from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Create a simple database with users for demonstration purposes.
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('user1', 'password123')")
    conn.commit()
    conn.close()

init_db()  # Initialize the database

# HTML template for login page
LOGIN_PAGE = """
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
    <h2>Login Page</h2>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    {% if error %}
        <p style="color:red;">Invalid credentials, please try again.</p>
    {% endif %}
</body>
</html>
"""

# HTML template for dashboard page
DASHBOARD_PAGE = """
<!doctype html>
<html lang="en">
<head><title>Dashboard</title></head>
<body>
    <h2>Welcome to the Dashboard!</h2>
    <a href="{{ url_for('login') }}">Logout</a>
</body>
</html>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('dashboard'))
        else:
            error = True

    return render_template_string(LOGIN_PAGE, error=error)

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    app.run(debug=True)