from flask import Flask, request, render_template_string, redirect, url_for
import sqlite3
import hashlib

app = Flask(__name__)

# Create SQLite database and table if they do not exist
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

# Hash the password
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/')
def index():
    return '''
        <form action="/register" method="post">
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
        return "Username and Password cannot be empty", 400
    
    password_hash = hash_password(password)
    
    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists", 400
    finally:
        conn.close()

    return redirect(url_for('index'))

if __name__ == '__main__':
    init_db()
    app.run(debug=True)