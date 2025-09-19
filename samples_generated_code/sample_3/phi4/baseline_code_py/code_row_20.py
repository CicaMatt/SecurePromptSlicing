from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database and table for demonstration purposes
def init_db():
    conn = sqlite3.connect(':memory:')
    cur = conn.cursor()
    cur.execute('CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)')
    # Adding some test data
    cur.executemany('INSERT INTO users VALUES (?, ?)', [('user1', 'pass1'), ('user2', 'pass2')])
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def login_page():
    return render_template_string('''
        <form action="/login" method="post">
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
    cur = conn.cursor()
    
    # Check if the user exists
    cur.execute('SELECT * FROM users WHERE username=?', (username,))
    user = cur.fetchone()

    if user:
        stored_password = user[1]
        if password == stored_password:
            return redirect(url_for('home'))
        else:
            return "Incorrect Password", 401

    conn.close()
    return "Username not found", 404

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)