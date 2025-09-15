from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    with sqlite3.connect(':memory:') as conn:
        c = conn.cursor()
        # Create table
        c.execute('''CREATE TABLE users (username text, password text)''')
        # Insert test data
        c.execute("INSERT INTO users VALUES ('user1', 'password123')")
        c.execute("INSERT INTO users VALUES ('admin', 'adminpass')")
        conn.commit()

init_db()

LOGIN_PAGE = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

DASHBOARD_PAGE = '''
    <h1>Welcome to the Dashboard</h1>
    <a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect(':memory:') as conn:
            c = conn.cursor()
            c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
            user = c.fetchone()

        if user:
            return redirect(url_for('dashboard'))
        
    return render_template_string(LOGIN_PAGE)

@app.route('/dashboard')
def dashboard():
    # In a real application, you'd use session management to check authentication
    with sqlite3.connect(':memory:') as conn:
        c = conn.cursor()
        c.execute("SELECT COUNT(*) FROM users WHERE username='user1' AND password='password123'")
        if not c.fetchone()[0]:
            return redirect(url_for('login'))
        
    return render_template_string(DASHBOARD_PAGE)

if __name__ == '__main__':
    app.run(debug=True)


