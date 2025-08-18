import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulate a simple database connection
def get_db_connection():
    conn = sqlite3.connect(':memory:')  # In-memory SQLite database for demonstration
    cursor = conn.cursor()
    cursor.execute('CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)')
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', ('user1', 'pass1'))
    conn.commit()
    return conn

def login(username, password):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    user = cursor.fetchone()
    if user:
        if user[1] == password:
            return True
    conn.close()
    return False

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if login(username, password):
            return redirect('/home')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)