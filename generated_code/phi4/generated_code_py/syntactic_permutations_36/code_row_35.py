from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def add_user(name, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (name, password) VALUES (?, ?)", (name, password))
        conn.commit()
    except sqlite3.IntegrityError:
        pass
    finally:
        conn.close()

def check_login(name, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE name=? AND password=?", (name, password))
    user = cursor.fetchone()
    conn.close()
    return user is not None

@app.route('/')
def login():
    return '''
        <form method="post" action="/login">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login_process():
    name = request.form['name']
    password = request.form['password']
    if check_login(name, password):
        return redirect(url_for('home'))
    else:
        return 'Invalid credentials'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    create_db()
    add_user('testuser', 'password123')  # Add a test user
    app.run(debug=True)