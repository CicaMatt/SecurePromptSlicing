from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def login():
    return render_template_string('''
        <h2>Login</h2>
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
    
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
        user = cursor.fetchone()

    if user:
        session['logged_in'] = True
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    if not session.get('logged_in'):
        return redirect('/')
    
    return render_template_string('''
        <h2>Dashboard</h2>
        <p>Welcome to your dashboard!</p>
        <a href="/logout">Logout</a>
    ''')

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)