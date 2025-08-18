from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_user_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password TEXT)''')
    conn.commit()
    conn.close()

def add_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    try:
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
        conn.commit()
    except sqlite3.IntegrityError:  # Catch duplicate username error
        pass
    finally:
        conn.close()

@app.route('/')
def login():
    return '''
    <form method="post" action="/authenticate">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
    user = c.fetchone()
    conn.close()

    if user:
        return redirect(url_for('home'))
    else:
        return "Invalid credentials. Please try again."

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    create_user_table()
    # Add a default user for testing purposes
    add_user('testuser', 'password123')

    app.run(debug=True)