from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
        conn.close()

        if user:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_page'))

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

@app.route('/login_page')
def login_page():
    return redirect(url_for('login'))

if __name__ == '__main__':
    conn = sqlite3.connect('users.db')
    conn.execute('''CREATE TABLE IF NOT EXISTS users
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  username TEXT NOT NULL,
                  password TEXT NOT NULL)''')
    conn.close()
    
    # For demonstration purposes, adding a sample user to the database
    conn = get_db_connection()
    conn.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', ('user1', 'pass123'))
    conn.commit()
    conn.close()

    app.run(debug=True)