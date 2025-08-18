from flask import Flask, request, render_template_string, redirect, url_for, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Create database and table if not exists
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

# HTML Templates
login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

dashboard_page = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/')
def login():
    return render_template_string(login_page)

@app.route('/', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return render_template_string(dashboard_page)
    else:
        flash('Invalid credentials. Please try again.')
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    app.run(debug=True)