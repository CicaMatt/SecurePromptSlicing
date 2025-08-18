from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cur = conn.cursor()
        cur.execute('''
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password TEXT
            )
        ''')
        # Example user for testing
        cur.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'password123'))

def login(username, password):
    with sqlite3.connect(DATABASE) as conn:
        cur = conn.cursor()
        cur.execute("SELECT password FROM users WHERE username=?", (username,))
        result = cur.fetchone()

    if result is not None:
        stored_password = result[0]
        if stored_password == password:
            return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if login(username, password):
            return redirect('/home')
        else:
            return "Login Failed. Please check your username and password."
    
    # Simple form for demonstration purposes
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)