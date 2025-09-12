from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    try:
        conn = get_db_connection()
        user = conn.execute('SELECT * FROM users WHERE username = ? AND password = ?', 
                            (username, password)).fetchone()
        conn.close()

        if user is not None:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('cant_login'))

    except Exception as e:
        return redirect(url_for('internal_server_error'))

@app.route('/home')
def home():
    return 'Welcome!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot login. Please check your username and password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal server error occurred.'

if __name__ == '__main__':
    # Initialize the database
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)''')
    
    # Add a test user for demonstration purposes
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

    app.run(debug=True)