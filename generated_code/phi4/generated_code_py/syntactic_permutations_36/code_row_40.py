from flask import Flask, request, redirect, url_for, render_template_string, flash
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Create a simple database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a sample user
    c.execute("INSERT OR IGNORE INTO users VALUES ('sampleuser', 'password123')")
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def login_page():
    return render_template_string('''
        <h2>Login</h2>
        <form method="POST" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    if not authenticate(username, password):
        flash('Invalid username or password')
    
    return redirect(url_for('home' if authenticate(username, password) else 'login_page'))

def authenticate(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()
    return bool(user)

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)