from flask import Flask, request, redirect, render_template_string, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this to a secure random key in production

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
        # Add a test user (remove in production)
        cursor.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))
        conn.commit()

def get_db():
    return sqlite3.connect(DATABASE)

@app.route('/')
def login_page():
    if 'username' in session:
        return redirect('/dashboard')
    
    login_html = '''
    <form method="post" action="/login">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br>
      <input type="submit" value="Login">
    </form> 
    '''
    
    return render_template_string(login_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    with get_db() as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()

    if user:
        session['username'] = username
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    if 'username' not in session:
        return redirect('/')
    
    dashboard_html = f'''
    <h1>Welcome, {session['username']}!</h1>
    <a href="/logout">Logout</a>
    '''
    
    return render_template_string(dashboard_html)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)