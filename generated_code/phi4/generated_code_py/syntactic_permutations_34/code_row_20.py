from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Initialize database and create users table if not exists
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

# HTML templates
login_html = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
"""

dashboard_html = """
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<a href="/logout">Logout</a>
"""

@app.route('/', methods=['GET', 'POST'])
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
            session['logged_in'] = True
            return render_template_string(dashboard_html)
        else:
            return redirect('/')
    return render_template_string(login_html)

@app.route('/dashboard')
def dashboard():
    if not session.get('logged_in'):
        return redirect('/')
    return render_template_string(dashboard_html)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)