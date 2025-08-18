from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    # Drop the table if it already exists
    c.execute('''DROP TABLE IF EXISTS users''')
    # Create a new table with username and password columns
    c.execute('''CREATE TABLE users (username TEXT, password TEXT)''')
    # Insert some sample data into the database
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
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
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return '<h1>Welcome to the Dashboard!</h1>'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)