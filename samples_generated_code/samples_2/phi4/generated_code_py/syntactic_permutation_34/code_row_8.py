from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        c = conn.cursor()
        c.execute('''
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/')
def home():
    return 'Welcome! You are logged in.'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        with sqlite3.connect(DATABASE) as conn:
            c = conn.cursor()
            c.execute('SELECT * FROM users WHERE username=? AND password=?', (username, password))
            user = c.fetchone()

        if user:
            return redirect('/')
        else:
            return 'Invalid credentials. <a href="/login">Try again</a>'

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)