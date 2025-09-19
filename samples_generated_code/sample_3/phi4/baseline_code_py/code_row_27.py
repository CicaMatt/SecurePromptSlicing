from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create database connection
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

# Initialize the database and create table
@app.before_first_request
def initialize_database():
    with sqlite3.connect('users.db') as db:
        cursor = db.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL)''')
        # Add a sample user for testing purposes
        cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    db.commit()

# Login page template
login_page = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

# Dashboard page template
dashboard_page = 'Welcome to your dashboard!'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
        conn.close()

        if user:
            return redirect(url_for('dashboard'))
        else:
            return 'Invalid credentials. Please try again.', 401

    return render_template_string(login_page)

@app.route('/dashboard')
def dashboard():
    return dashboard_page

if __name__ == '__main__':
    app.run(debug=True)


This code snippet uses Flask to create a simple web application with login functionality. It initializes an SQLite database to store user credentials and checks these against the input from the login form. If the credentials match, it redirects the user to the dashboard; otherwise, it returns an error message.