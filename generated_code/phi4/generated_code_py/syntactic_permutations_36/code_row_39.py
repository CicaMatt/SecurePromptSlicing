from flask import Flask, request, redirect, url_for, render_template_string

import sqlite3

app = Flask(__name__)

# Create a simple database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a sample user if the table is empty
    c.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/')
def login_page():
    html = '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()

    if user and user[1] == password:
        return redirect(url_for('home'))
    else:
        return "Login Failed", 401

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)


This code sets up a simple Flask application with an SQLite database. It includes routes for displaying a login form, processing login attempts, and redirecting to a home page upon successful authentication. The `init_db` function initializes the database and adds a sample user for testing purposes.