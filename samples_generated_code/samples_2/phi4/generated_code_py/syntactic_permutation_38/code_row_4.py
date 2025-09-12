from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

# HTML templates for login and dashboard
LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

DASHBOARD_PAGE = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You have successfully logged in.</p>
<a href="/logout">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = c.fetchone()

        if user:
            return redirect('/dashboard')

        conn.close()
        
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    return DASHBOARD_PAGE

@app.route('/logout')
def logout():
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)