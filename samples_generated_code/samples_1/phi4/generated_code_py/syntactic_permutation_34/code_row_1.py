from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    # Create table
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert some sample data
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('user1', 'pass123')")
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('user2', 'password')")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/')
def login():
    return render_template_string('''
        <form action="/auth" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/auth', methods=['POST'])
def auth():
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
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)