from flask import Flask, request, redirect, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        c = conn.cursor()
        c.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def index():
    return render_template_string('''
        <form method="post" action="/register">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    # Hash the password
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                  salt, 100000)
    pwdhash = salt + pwdhash

    try:
        with sqlite3.connect(DATABASE) as conn:
            c = conn.cursor()
            c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                      (username, pwdhash.hex()))
            conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists. Please choose a different username."

    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)