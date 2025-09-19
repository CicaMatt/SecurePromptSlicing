from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple in-memory database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL
        )
    ''')
    # Add a sample user for testing purposes
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)




