from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def login_page():
    if 'username' in session:
        return redirect('/dashboard')
    
    login_form = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(login_form)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
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
    
    return f'<h1>Welcome to the Dashboard, {session["username"]}!</h1><br><a href="/logout">Logout</a>'

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

if __name__ == '__main__':
    conn = get_db_connection()
    
    # Create table if not exists
    conn.execute('''CREATE TABLE IF NOT EXISTS users (
                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                     username TEXT UNIQUE NOT NULL,
                     password TEXT NOT NULL)''')
    conn.close()

    # Insert a sample user (username: admin, password: secret)
    conn = get_db_connection()
    try:
        conn.execute('INSERT INTO users(username, password) VALUES (?, ?)', ('admin', 'secret'))
    except sqlite3.IntegrityError:
        pass
    conn.commit()
    conn.close()

    app.run(debug=True)