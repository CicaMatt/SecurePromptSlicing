from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    with app.app_context():
        db = get_db_connection()
        db.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
        db.commit()

@app.route('/')
def index():
    return '''
    <h1>Register</h1>
    <form method="post" action="/register">
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
        return 'Username and Password are required!', 400

    hashed_password = generate_password_hash(password)

    try:
        db = get_db_connection()
        db.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                   (username, hashed_password))
        db.commit()
    except sqlite3.IntegrityError:
        return 'Username already exists!', 400

    return redirect(url_for('index'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)