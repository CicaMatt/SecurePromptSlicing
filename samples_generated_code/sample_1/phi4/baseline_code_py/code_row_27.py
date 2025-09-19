from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a database and table if they don't exist
def init_db():
    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
        # Add a test user for demonstration purposes
        c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
        conn.commit()

# Initialize database
init_db()

# HTML templates
login_template = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

dashboard_template = '''
<!doctype html>
<title>Dashboard</title>
<h1>Welcome to the Dashboard!</h1>
<p><a href="/logout">Logout</a></p>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect('users.db') as conn:
            c = conn.cursor()
            c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
            user = c.fetchone()

            if user:
                return redirect(url_for('dashboard'))
    
    return render_template_string(login_template)

@app.route('/dashboard')
def dashboard():
    return render_template_string(dashboard_template)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)


