from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    return '''
        <form action="/register" method="post">
            <input type="text" name="username" placeholder="Username" required>
            <input type="password" name="password" placeholder="Password" required>
            <button type="submit">Register</button>
        </form>
    '''

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    hashed_password = generate_password_hash(password)

    conn = get_db_connection()
    try:
        conn.execute('INSERT INTO users (username, password) VALUES (?, ?)', 
                     (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return 'Username already exists. Please choose a different username.'
    finally:
        conn.close()

    return redirect(url_for('index'))

@app.cli.command('init-db')
def init_db():
    with app.app_context():
        db = get_db_connection()
        db.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL
                    )''')
        db.commit()

if __name__ == '__main__':
    with sqlite3.connect(DATABASE) as conn:
        conn.execute('PRAGMA foreign_keys = ON;')
        conn.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL
                        )''')

    app.run(debug=True)