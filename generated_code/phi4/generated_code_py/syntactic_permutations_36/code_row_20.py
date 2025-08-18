from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password TEXT NOT NULL
            )
        ''')
        # Add a sample user for testing (remove or modify in production)
        cursor.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('testuser', 'password123'))
    conn.commit()

def login(username, password):
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username=?', (username,))
        user = cursor.fetchone()
        if user and user[1] == password:
            return True
        return False

@app.route('/')
def login_page():
    html = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    if login(username, password):
        return redirect(url_for('home'))
    else:
        return 'Login Failed. Please try again.'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)