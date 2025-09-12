from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

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
    html_form = '''
    <form method="post" action="/register">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Register">
    </form> 
    '''
    return render_template_string(html_form)

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    
    if not username or not password:
        return "Username and Password are required", 400

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        with sqlite3.connect(DATABASE) as conn:
            cursor = conn.cursor()
            cursor.execute('''
                INSERT INTO users (username, password_hash)
                VALUES (?, ?)
            ''', (username, password_hash))
            conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists", 400

    return "Registration successful!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)