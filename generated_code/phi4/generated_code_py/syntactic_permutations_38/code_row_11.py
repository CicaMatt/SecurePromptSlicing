from flask import Flask, request, redirect, url_for, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)''')
    # Adding a sample user
    c.execute("INSERT INTO users VALUES ('user1', 'password123')")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/')
def login():
    return render_template_string('''
        <h2>Login</h2>
        <form method="post" action="/authenticate">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    
    if c.fetchone() is not None:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return '<h2>Welcome to the Dashboard!</h2>'

if __name__ == '__main__':
    app.run(debug=True)


This code uses Flask for web handling and SQLite3 for a simple in-memory database. It doesn't persist data, so the user needs to be re-added each time you run it. This setup is suitable for demonstration purposes only and not secure for production use.