from flask import Flask, request, redirect, render_template_string, url_for
import sqlite3

app = Flask(__name__)

# Create a simple database with users for demonstration purposes.
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a test user
    cursor.execute("INSERT OR IGNORE INTO users VALUES ('testuser', 'testpassword')")
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET'])
def login():
    return render_template_string('''
        <form method="POST" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = cursor.fetchone()
    conn.close()

    if user:
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

@app.route('/')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)