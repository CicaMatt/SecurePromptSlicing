from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create a simple SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Insert some test data if the table is empty
    c.execute("SELECT COUNT(*) FROM users")
    if c.fetchone()[0] == 0:
        c.execute("INSERT INTO users VALUES ('testuser', 'password123')")
        conn.commit()
    conn.close()

# Initialize database
init_db()

@app.route('/')
def login():
    return render_template_string('''
    <form method="post" action="/authenticate">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)