from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates
login_page_html = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    {% if error %}
        <p style="color:red;">Invalid username or password. Please try again.</p>
    {% endif %}
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

dashboard_page_html = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
    <h2>Welcome to the Dashboard!</h2>
    <a href="/logout">Logout</a>
</body>
</html>
'''

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return render_template_string(login_page_html, error=True)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page_html)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)