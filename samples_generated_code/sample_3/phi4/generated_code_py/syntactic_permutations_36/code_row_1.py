from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    c.execute("INSERT INTO users (username, password) VALUES ('testuser', 'password123')")  # Example user
    conn.commit()
    conn.close()

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()

    if user and user[1] == password:
        return redirect(url_for('home'))
    else:
        return 'Invalid credentials', 401

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    create_db()
    app.run(debug=True)