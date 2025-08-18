from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

HTML_LOGIN_FORM = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post" action="/login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
"""

HTML_HOME_PAGE = """
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
"""

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a test user
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123') ON CONFLICT(username) DO NOTHING")
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
        conn.close()

        if user:
            return redirect(url_for('home'))
        else:
            return render_template_string(HTML_LOGIN_FORM + "<p>Invalid credentials. Please try again.</p>")
    else:
        return render_template_string(HTML_LOGIN_FORM)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)