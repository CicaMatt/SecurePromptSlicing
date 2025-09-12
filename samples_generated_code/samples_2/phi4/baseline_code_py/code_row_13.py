from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple database with users table for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    c.execute("INSERT OR IGNORE INTO users VALUES ('user1', 'password123')")
    c.execute("INSERT OR IGNORE INTO users VALUES ('admin', 'adminpass')")
    conn.commit()
    conn.close()

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()

    if user and user[1] == password:
        return redirect('/home')

    return "Login failed. Invalid username or password."

@app.route('/home')
def home():
    return "<h1>Welcome to the Home Page!</h1>"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)