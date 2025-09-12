import sqlite3
from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database connection and schema for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)''')
    # Insert a mock user for testing
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'testpassword')")
    conn.commit()
    conn.close()

def check_user_credentials(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return user is not None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_user_credentials(username, password):
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
    init_db()
    app.run(debug=True)