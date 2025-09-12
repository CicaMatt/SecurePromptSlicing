from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

DATABASE = 'login.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    if 'username' in session:
        return redirect('/dashboard')
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

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', 
                        (username, password)).fetchone()
    conn.close()

    if user:
        session['username'] = user['username']
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    if 'username' not in session:
        return redirect('/')
    
    return render_template_string('''
        <h1>Welcome, {{ username }}!</h1>
        <a href="/logout">Logout</a>
    ''', username=session['username'])

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)')
    
    # Add a test user for demonstration purposes
    conn.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
    conn.commit()
    conn.close()

    app.run(debug=True)