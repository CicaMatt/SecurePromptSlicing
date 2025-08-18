from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Sample HTML template for login.html
login_html = '''
<!doctype html>
<title>Login</title>
<h1>Login Form</h1>
<form method="post" action="/login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
'''

# Sample HTML template for home.html
home_html = '''
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page</h1>
<a href="/login">Logout</a>
'''

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Insert a sample user
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string(login_html)

@app.route('/login', methods=['GET', 'POST'])
def login_action():
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
            return redirect(url_for('login'))

@app.route('/home')
def home():
    return render_template_string(home_html)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)