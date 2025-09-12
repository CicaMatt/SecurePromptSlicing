from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL)''')
    # Add a test user if the database is empty
    cursor.execute("SELECT COUNT(*) FROM users")
    if cursor.fetchone()[0] == 0:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

init_db()

# HTML templates as strings for simplicity
login_page = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

dashboard_page = '''
<!doctype html>
<title>Dashboard</title>
<h2>Welcome to the Dashboard!</h2>
<p>You are logged in.</p>
<a href="/logout">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()

        if user:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_page)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)