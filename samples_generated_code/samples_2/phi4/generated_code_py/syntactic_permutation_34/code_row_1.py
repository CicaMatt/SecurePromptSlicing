from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML templates as strings for simplicity
LOGIN_PAGE_TEMPLATE = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

DASHBOARD_PAGE_TEMPLATE = '<h1>Welcome to the Dashboard</h1>'

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
    conn.close()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return render_template_string(DASHBOARD_PAGE_TEMPLATE)

def init_db():
    conn = sqlite3.connect('users.db')
    cur = conn.cursor()
    cur.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)''')
    # Example user for testing
    cur.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

if __name__ == '__main__':
    init_db()  # Initialize the database and create tables if they don't exist
    app.run(debug=True)