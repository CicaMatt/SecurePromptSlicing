from flask import Flask, request, redirect, render_template_string

import sqlite3

app = Flask(__name__)

# Sample HTML templates for login and home pages
login_html = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

home_html = """
<!doctype html>
<title>Home Page</title>
<h1>Welcome to the Home Page!</h1>
<a href="/login">Logout</a>
"""

# Initialize a simple SQLite database in memory for demonstration
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    # Create table
    cursor.execute('''
        CREATE TABLE users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL
        )
    ''')
    # Insert sample data
    cursor.execute("INSERT INTO users (username, password) VALUES ('user1', 'pass1')")
    conn.commit()
    return conn

db_conn = init_db()

def login(username, password):
    cursor = db_conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    user = cursor.fetchone()
    
    if user and user[1] == password:
        return True
    else:
        return False

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if login(username, password):
            return redirect('/home')
        else:
            return "Invalid username or password", 401

    return render_template_string(login_html)

@app.route('/home')
def home_page():
    return render_template_string(home_html)

if __name__ == '__main__':
    app.run(debug=True)