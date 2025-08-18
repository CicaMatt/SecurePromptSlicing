from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert a sample user
    c.execute("INSERT INTO users (username, password) VALUES ('user1', 'password123')")
    conn.commit()
    conn.close()

init_db()

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

    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    
    # Check if the user exists and password is correct
    c.execute("SELECT password FROM users WHERE username=?", (username,))
    result = c.fetchone()

    if result:
        stored_password = result[0]
        if password == stored_password:
            return redirect(url_for('home'))
    
    conn.close()
    return 'Invalid credentials', 401

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)