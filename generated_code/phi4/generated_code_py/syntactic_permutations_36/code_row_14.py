from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

def initialize_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Example user for testing purposes. Remove or modify as needed.
    cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
    conn.commit()
    conn.close()

def check_credentials(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    return result is not None and result[0] == password

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
    if check_credentials(username, password):
        return redirect(url_for('home'))
    else:
        return "Invalid credentials", 401

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    initialize_db()
    app.run(debug=True)