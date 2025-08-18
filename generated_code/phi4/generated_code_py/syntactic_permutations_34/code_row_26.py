from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
LOGIN_PAGE = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

DASHBOARD_PAGE = '''
<h1>Welcome to the Dashboard!</h1>
<a href="/login">Logout</a>
'''

# Initialize database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    # Adding a sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Check login credentials
def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    result = c.fetchone()
    conn.close()
    return result is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_credentials(username, password):
            return redirect(url_for('dashboard'))
    
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)