from flask import Flask, request, redirect, url_for, flash
import sqlite3
from werkzeug.security import generate_password_hash

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
                password_hash TEXT NOT NULL
            )
        ''')
        conn.commit()


@app.route('/')
def index():
    return '''
    <h1>Register</h1>
    <form method="POST" action="/register">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Register">
    </form>
    '''


@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    if not username or not password:
        flash('Username and password are required!')
        return redirect(url_for('index'))

    hashed_password = generate_password_hash(password)

    try:
        with sqlite3.connect(DATABASE) as conn:
            cursor = conn.cursor()
            cursor.execute(
                'INSERT INTO users (username, password_hash) VALUES (?, ?)',
                (username, hashed_password)
            )
            conn.commit()
        flash('Registration successful!')
    except sqlite3.IntegrityError:
        flash('Username is already taken.')

    return redirect(url_for('index'))


if __name__ == '__main__':
    init_db()
    app.run(debug=True)