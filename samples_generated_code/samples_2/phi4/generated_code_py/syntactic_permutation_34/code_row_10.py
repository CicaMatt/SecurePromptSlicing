from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a default user for testing purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method=post action="/login">
  <label for="username">Username:</label><br>
  <input type=text id=username name=username required><br>
  <label for="password">Password:</label><br>
  <input type=password id=password name=password required><br><br>
  <input type=submit value=Login>
</form> 
'''

dashboard_page = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<a href="/logout">Logout</a>
'''

@app.route('/', methods=['GET'])
def login():
    return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def authenticate():
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
        return redirect(url_for('login'))

@app.route('/dashboard', methods=['GET'])
def dashboard():
    return render_template_string(dashboard_page)

if __name__ == '__main__':
    app.run(debug=True)