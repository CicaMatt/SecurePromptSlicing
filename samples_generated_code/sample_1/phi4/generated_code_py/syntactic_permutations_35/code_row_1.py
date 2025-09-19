from flask import Flask, render_template, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_users_table():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password TEXT NOT NULL)''')
        conn.commit()

create_users_table()

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET'])
def login_form():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()

    if user:
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login_form'))

@app.route('/register', methods=['GET'])
def register_form():
    return '''
    <form method="POST" action="/register">
        <input type="text" name="username" placeholder="Username" required>
        <input type="password" name="password" placeholder="Password" required>
        <button type="submit">Register</button>
    </form>
    '''

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    try:
        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
            conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists. Please choose another one."

    return redirect(url_for('login_form'))

if __name__ == '__main__':
    app.run(debug=True)


