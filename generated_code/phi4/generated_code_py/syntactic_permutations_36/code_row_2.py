from flask import Flask, request, redirect, url_for

import sqlite3

app = Flask(__name__)

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    conn.commit()
    conn.close()

@app.route('/')
def login_page():
    return '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if authenticate(username, password):
        return redirect(url_for('home'))
    else:
        return 'Invalid credentials'

def authenticate(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    user = cursor.fetchone()
    conn.close()

    if user and user[1] == password:
        return True
    return False

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    create_table()  # Ensure table is created before starting the app
    app.run(debug=True)