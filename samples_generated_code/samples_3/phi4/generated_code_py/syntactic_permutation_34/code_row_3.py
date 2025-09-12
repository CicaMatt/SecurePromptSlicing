from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes.
conn = sqlite3.connect(':memory:', check_same_thread=False)
c = conn.cursor()

# Create a users table and insert a sample user for testing.
c.execute('''
    CREATE TABLE users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        password TEXT NOT NULL
    )
''')
c.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
conn.commit()

@app.route('/')
def login():
    html = '''
    <form method="post" action="/login">
        <input type="text" name="username" placeholder="Username" required><br>
        <input type="password" name="password" placeholder="Password" required><br>
        <button type="submit">Login</button>
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login_action():
    username = request.form['username']
    password = request.form['password']

    c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
    user = c.fetchone()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)