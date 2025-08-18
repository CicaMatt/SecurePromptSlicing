from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    password TEXT NOT NULL)''')
    # Add a test user for demonstration purposes
    c.execute("INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)", ('testuser', 'testpassword'))
    conn.commit()
    conn.close()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        return handle_login(username, password)

    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

def handle_login(username, password):
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()

    c.execute("SELECT password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if result:
        stored_password = result[0]
        if password == stored_password:
            return redirect('/home')
    
    return 'Invalid login. Please try again.'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)