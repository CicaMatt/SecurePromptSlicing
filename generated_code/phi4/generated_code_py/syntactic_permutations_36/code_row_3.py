from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    # Add a sample user for testing purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('testuser', 'password123')")
    conn.commit()
    conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()
    conn.close()
    if user and user[1] == password:
        return True
    return False

create_database()

@app.route('/')
def login_page():
    html_form = '''
        <form method="POST" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(html_form)

@app.route('/login', methods=['POST'])
def login_handler():
    username = request.form['username']
    password = request.form['password']
    if login(username, password):
        return redirect(url_for('home'))
    else:
        return "Invalid credentials", 401

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)


