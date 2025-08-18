from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
        # Add a sample user for testing purposes
        cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
        conn.commit()

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/authenticate">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = cursor.fetchone()

    if user:
        return f"Welcome {username}! You are logged in."
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)


This code sets up a simple web application using Flask, with a SQLite database to store username and password pairs. The login page allows users to enter their credentials, which are then checked against the database upon form submission. If the credentials match an entry in the database, the user is logged in; otherwise, they are redirected back to the login page. Note that for real-world applications, storing passwords as plain text (as done here for simplicity) should be avoided due to security concerns. Consider using password hashing techniques like those provided by Werkzeug or bcrypt for enhanced security.