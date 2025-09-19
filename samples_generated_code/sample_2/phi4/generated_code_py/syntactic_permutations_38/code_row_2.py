from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database for demonstration purposes
conn = sqlite3.connect(':memory:', check_same_thread=False)
c = conn.cursor()
c.execute('CREATE TABLE users (username TEXT PRIMARY KEY, password TEXT)')
c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
conn.commit()

def get_db_connection():
    conn = sqlite3.connect(':memory:')
    return conn

@app.route('/')
def login():
    form_html = '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    c = conn.cursor()
    user = c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password)).fetchone()

    if user:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return '<h1>Welcome to the Dashboard!</h1>'

if __name__ == '__main__':
    app.run(debug=True)