from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

HTML_LOGIN_PAGE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

HTML_HOME_PAGE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome to the Home Page!</h2>
    <a href="/login">Logout</a>
</body>
</html>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT, password TEXT)''')
    # Add a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def home():
    return HTML_HOME_PAGE

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect(url_for('home'))
        else:
            return "Invalid credentials. <a href='/login'>Try again</a>."

    return render_template_string(HTML_LOGIN_PAGE)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)