from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
        conn.close()

        if user:
            stored_password_hash = user['password']
            # For simplicity we are comparing plaintext passwords. In a real application you should hash the password
            if password == stored_password_hash:
                return redirect(url_for('home'))
        
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    # Initialize database for demonstration purposes
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password TEXT)')
    conn.commit()

    # Adding a test user
    try:
        conn.execute('INSERT INTO users (username, password) VALUES (?, ?)', ('testuser', 'testpassword'))
        conn.commit()
    except sqlite3.IntegrityError:
        pass

    conn.close()

    app.run(debug=True)