import sqlite3
from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Create an SQLite database or connect if it already exists
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

init_db()

@app.route('/')
def index():
    return render_template_string('''
        <form method="POST" action="/register">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    
    if not username or not password:
        return "Username and password are required."

    hashed_password = generate_password_hash(password)

    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists."
    finally:
        conn.close()

    return "Registration successful."

if __name__ == '__main__':
    app.run(debug=True)